#include "jui/gfx/freetype_font.hpp"

namespace JUI
{

    // Constant character codes.
    const FT_ULong NEW_LINE = '\n';
    const FT_ULong SPACE = ' ';
    const FT_ULong SLASH = '/';
    const FT_ULong DASH = '-';

    /*
     * Font constructor.
     */
    FreetypeFont::FreetypeFont( FT_Face face )
    {
        // Add reference count.
        face_ = face;
        FT_Reference_Face( face );

        // Null/zero lists and textures.
        list_ = 0;
    }

    /*
     * Font destructor.
     */
    FreetypeFont::~FreetypeFont( void )
    {
        // Close the face.
        FT_Done_Face( face_ );

        // Delete textures.
        size_t textures_length = textures_.get_length();
        if (textures_length != 0) {
            glDeleteTextures( textures_length, textures_.get_buffer() );
            textures_.clear();
        }

        // Delete list.
        unsigned int glyph_count = face_->num_glyphs;
        if (list_ != 0) {
            glDeleteLists( list_, glyph_count );
        }
        
        // Delete advances.
        advances_.clear();
    }

    /*
     * Initialize resources for font.
     */
    bool FreetypeFont::initialize( void )
    {
        // Generate renderable glyphs.
        FreetypeFont::ReturnStatus error = generate_glyphs();
        if (error != Success) {
            return false;
        }

        return true;
    }

    /*
     * Release resources for font.
     */
    void FreetypeFont::release( void )
    {
        delete this;
    }

    /*
     * Generate glyph textures and lists for rendering them.
     */
    FreetypeFont::ReturnStatus FreetypeFont::generate_glyphs( void )
    {
        // Generate textures for glyphs.
        unsigned int glyph_count = face_->num_glyphs;
        if (!textures_.set_length( glyph_count )) {
            return NoMemoryFailure;
        }

        // Generate lists.
        glGenTextures( glyph_count, textures_.get_buffer() );
        list_ = glGenLists( glyph_count );
        if (list_ == 0) {
            return GenerateListFailure;
        }

        // Generate list of advances for characters.
        if (!advances_.set_length( glyph_count )) {
            return NoMemoryFailure;
        }

        // Generate advances and lists for glyphs.
        FreetypeFont::ReturnStatus error = create_display_lists();
        if (error != Success) {
            return error;
        }

        return Success;
    }

    /*
     * Create OpenGL display list of textures.
     */
    FreetypeFont::ReturnStatus FreetypeFont::create_display_lists( void )
    {
        // Generate display lists for all characters.
        FT_UInt index;
        for (FT_ULong i = FT_Get_First_Char( face_, &index); i != 0; i = FT_Get_Next_Char( face_, i, &index )) {
            // Load the glyph for the character.
            FT_Error error = FT_Load_Glyph( face_, index, FT_LOAD_DEFAULT );
            if (error != 0) {
                return LoadGlyphFailure;
            }

            // Render the glyph.
            error = FT_Render_Glyph( face_->glyph, FT_RENDER_MODE_NORMAL );
            if (error != 0) {
                return RenderGlyphFailure;
            }

            // Get the texture size.
            FT_Bitmap& bitmap = face_->glyph->bitmap;
            GLsizei width = OpenGLShared::next_power_of_2( bitmap.width );
            GLsizei height = OpenGLShared::next_power_of_2( bitmap.rows );

            // Create buffer for pixels.
            const unsigned int SRC_BPP = 1;
            const unsigned int DEST_BPP = 2;
            unsigned int tex_buffer_size = DEST_BPP * width * height;
            GLubyte* tex_buffer = (GLubyte*)malloc( tex_buffer_size );
            if (tex_buffer == nullptr) {
                return NoMemoryFailure;
            }
            const GLsizei DEST_ROW_WIDTH = DEST_BPP * width;
            const GLsizei DEST_SRC_WIDTH = DEST_BPP * bitmap.width;
            const GLsizei ROW_REMAINDER = DEST_ROW_WIDTH - DEST_BPP * bitmap.width;

            // Fill in alpha and colour.
            for (GLsizei y = 0; y < bitmap.rows; ++y) {
                GLubyte* row_start = tex_buffer + y * DEST_ROW_WIDTH;
                for (GLsizei x = 0; x < bitmap.width; ++x) {
                    unsigned int src_index = SRC_BPP * (x + bitmap.width * y);
                    unsigned int dest_index = DEST_BPP * (x + y * width);
                    tex_buffer[ dest_index ] = 0xff;
                    tex_buffer[ dest_index + 1 ]  = bitmap.buffer[ src_index ];
                }

                // Zero the rest.
                memset( row_start + DEST_SRC_WIDTH, 0, ROW_REMAINDER);
            }

            // Set up texture params.
            GLuint texture = textures_.get( index );
            glBindTexture( GL_TEXTURE_2D, texture );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

            // Store character advance.
            advances_.set( index, face_->glyph->advance.x >> 6 );

            // Create texture from the buffer.
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
                width, height, 0,
                GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
                tex_buffer );
            free( tex_buffer );

            // Create display list for this character.
            glNewList( list_ + index, GL_COMPILE );
            glBindTexture( GL_TEXTURE_2D, texture );
            glPushMatrix();

            // Place the character properly.
            glTranslatef( static_cast<float>(face_->glyph->bitmap_left), 0.0f, 0.0f );
            glTranslatef( 0, static_cast<float>((face_->size->metrics.ascender >> 6) - face_->glyph->bitmap_top), 0.0f );

            // Get texture coordinates (due to power-of-2 rule).
            float x = static_cast<float>(bitmap.width) / static_cast<float>(width);
            float y = static_cast<float>(bitmap.rows) / static_cast<float>(height);

            // Draw texture mapped quad.
            glBegin( GL_QUADS );
                glTexCoord2f( 0.0f, 0.0f );
                glVertex2f( 0.0f, 0.0f );

                glTexCoord2f( x, 0.0f );
                glVertex2i( bitmap.width, 0 );

                glTexCoord2f( x, y );
                glVertex2i( bitmap.width, bitmap.rows );

                glTexCoord2f( 0.0f, y );	
                glVertex2i( 0, bitmap.rows );
            glEnd();
            glPopMatrix();

            // Move forward by the character's advance.
            glTranslatef( static_cast<float>(face_->glyph->advance.x >> 6), 0.0f, 0.0f );
            glBindTexture( GL_TEXTURE_2D, 0 );
            glEndList();
        }

        return Success;
    }

    /*
     * Draw character to screen.
     */
    void FreetypeFont::draw_char( FT_ULong c ) const
    {
        FT_UInt index = FT_Get_Char_Index( face_, c );
        if (index != 0) {
            glCallList( list_ + index );
        }
    }

    /*
     * Push draw position to new line.
     */
    void FreetypeFont::new_line( void ) const
    {
        float baseline_spacing = static_cast<float>(get_baseline_spacing());
        glTranslatef( 0.0f, baseline_spacing, 0.0f );
    }

    /*
     * Get the width of a glyph.
     */
    FT_Pos FreetypeFont::get_char_width( FT_ULong c ) const
    {
        FT_UInt index = FT_Get_Char_Index( face_, c );
        if (index != 0) {
            return advances_.get( index );
        }

        return 0;
    }

    /*
     * Get width of a string.
     */
    FT_Pos FreetypeFont::get_string_width( const RenderableStringInterface* text, size_t start, size_t end ) const
    {
        FT_Pos width = 0L;
        for (size_t i = start; i < end; ++i) {
            unsigned int character_code = text->get_character_code( i );
            width += get_char_width( character_code );
        }

        return width;
    }

    /*
     * Generate a list for drawing a string.
     */
    void FreetypeFont::draw( RECT* rect, const RenderableStringInterface* text, size_t start, size_t end ) const
    {
        // Push matrix for line.
        glPushMatrix();

        // Keep track of new-lines and widest line.
        FT_Pos longest = 0L;
        FT_Pos current = 0L;
        unsigned int new_lines = 0;

        // Draw characters, split on new line.
        for (size_t i = start; i < end; ++i) {
            FT_ULong c = text->get_character_code( i );
            if (c == static_cast<FT_ULong>('\n')) {
                // Update longest line.
                if (current > longest) {
                    longest = current;
                    current = 0L;
                }

                // Reset line.
                glPopMatrix();
                new_lines++;
                new_line();
                glPushMatrix();
            }
            else {
                draw_char( c );
                current += get_char_width( c );
            }
        }

        // Do one more check for last line.
        if (current > longest) {
            longest = current;
        }

        // Set rect sizes.
        if (rect != nullptr) {
            rect->left = 0;
            rect->right = longest;
            rect->top = 0;
            rect->bottom = new_lines * get_baseline_spacing() + get_line_height();
        }

        glPopMatrix(); // End line matrix.
    }

    /*
     * Draw aligned text to the screen.
     */
    void FreetypeFont::draw_aligned( const RenderableStringInterface* text, size_t start, size_t end, float width, TextHorizontalAlignType align_type ) const
    {
        // Measure text.
        float text_width = static_cast<float>(get_string_width( text, start, end ));

        // Translate to alignment.
        glPushMatrix();
        switch (align_type) {
        case TEXT_ALIGN_CENTER:
            glTranslatef( (width - text_width) / 2.0f, 0.0f, 0.0f );
            break;
        case TEXT_ALIGN_RIGHT:
            glTranslatef( (width - text_width), 0.0f, 0.0f );
            break;
        }

        // Draw text.
        draw( nullptr, text, start, end );
        glPopMatrix();
    }

    /*
     * Prepare drawing of wrapped string.
     */
    void FreetypeFont::draw_wrapped( RECT* bounds, const RenderableStringInterface* text, TextHorizontalAlignType align_type ) const
    {
        // Constant bounds.
        const long LINE_WIDTH = bounds->right - bounds->left;

        // Line break variables.
        size_t line_start = 0;
        size_t break_point = 0;
        long width_left = LINE_WIDTH;
        long width_since_break = 0;
        unsigned int new_lines = 0;

        // Set local temporary transformation.
        glPushMatrix();

        size_t length = text->get_length();
        for (size_t i = 0; i < length; ++i) {
            FT_ULong ch = text->get_character_code( i );
            bool draw_line = false;
            bool include_breakpoint = true;
            
            if (ch == NEW_LINE) {
                // It has fit so far, draw until here.
                break_point = i;
                draw_line = true;
                width_since_break = 0;
            }
            else {
                // Move forward by character width.
                long char_width = get_char_width( ch );
                width_since_break += char_width;

                // Check if exceeding and if we have a break.
                bool exceeds_width = width_since_break > width_left;
                bool no_break = break_point == line_start;
                
                if (exceeds_width) {
                    if (ch == SPACE) {
                        // Use space to break line.
                        break_point = i;
                        width_since_break = 0;
                    }
                    else if (no_break) {
                        // Set break before this character.
                        break_point = i - 1;
                        width_since_break = char_width;
                    }
                    
                    draw_line = 1;
                }
                else if (ch == SPACE) {
                    // Reset width since break.
                    width_left -= width_since_break;
                    width_since_break = 0;

                    // Now set this as the break point.
                    break_point = i;
                    include_breakpoint = false;
                }
                else if (ch == DASH || ch == SLASH) {
                    // Reset width since break.
                    width_left -= width_since_break;
                    width_since_break = 0;

                    // Now set this as the break point.
                    break_point = i+1;
                }
            }
            
            if (draw_line) {
                draw_aligned( text, line_start, break_point, static_cast<float>(LINE_WIDTH), align_type );
                new_line();
                new_lines++;

                // Reset start of line and remaining width.
                line_start = break_point = break_point + (include_breakpoint ? 0 : 1);
                width_left = LINE_WIDTH;
            }
        }

        // Draw last line, since it fits.
        draw_aligned( text, line_start, length, static_cast<float>(LINE_WIDTH), align_type );

        // Adjust rect bounds by this size.
        bounds->bottom = bounds->top + (new_lines * get_baseline_spacing()) + get_line_height();
        glPopMatrix();
    }

    /*
     * Get the height of a line.
     */
    GLsizei FreetypeFont::get_line_height( void ) const
    {
        return face_->size->metrics.ascender >> 6;
    }

    /*
     * Get distance between lines.
     */
    GLsizei FreetypeFont::get_baseline_spacing( void ) const
    {
        return face_->size->metrics.height >> 6;
    }

}
