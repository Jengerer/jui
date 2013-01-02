#include "jui/gfx/graphics_2d.hpp"
#include "jui/application/error_stack.hpp"
#include <png.h>

namespace JUI
{        

    /*
     * Graphics constructor.
     */
    Graphics2D::Graphics2D( Window* window )
    {
        // Set window handle.
        window_ = window;

        // Null device and resource context.
        dc_ = nullptr;
        rc_ = nullptr;
    }

    /*
     * Graphics clean up.
     */
    Graphics2D::~Graphics2D( void )
    {
        clean_up();
    }

    /*
     * Initialize contexts and scene.
     */
    Graphics2D::ReturnStatus Graphics2D::initialize( void )
    {
        // Fill out pixel format.
        PIXELFORMATDESCRIPTOR pixelDesc;
        ZeroMemory( &pixelDesc, sizeof( pixelDesc ) );
        pixelDesc.nSize = sizeof( PIXELFORMATDESCRIPTOR );
        pixelDesc.nVersion = 1;
        pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pixelDesc.iPixelType = PFD_TYPE_RGBA;
        pixelDesc.cColorBits = 16;
        pixelDesc.iLayerType = PFD_MAIN_PLANE;
        pixelDesc.cDepthBits = 16;

        // Get device context.
        dc_ = GetDC( window_->get_handle() );
        if (dc_ == nullptr) {
            return GetDCFailure;
        }

        // Create window settings if fullscreen.
        if (window_->is_fullscreen()) {
            DEVMODE settings;
            memset( &settings, 0, sizeof(settings) );
            settings.dmSize = sizeof(settings);
            settings.dmPelsWidth = window_->get_width();
            settings.dmPelsHeight = window_->get_height();
            settings.dmBitsPerPel = 16;
            settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
            if (ChangeDisplaySettings( &settings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL) {
                return ChangeDisplaySettingsFailure;
            }
        }

        // Choose pixel format.
        GLuint pixelFormat = ChoosePixelFormat( dc_, &pixelDesc );
        if (pixelFormat == 0) {
            return ChoosePixelFormatFailure;
        }

        // Set received pixel format.
        if (!SetPixelFormat( dc_, pixelFormat, &pixelDesc )) {
            return SetPixelFormatFailure;
        }

        // Create GLRC handle.
        rc_ = wglCreateContext( dc_ );
        if (rc_ == nullptr) {
            return CreateRCFailure;
        }

        // Creating loading GLRC handle.
        loading_rc_ = wglCreateContext( dc_ );
        if (loading_rc_ == nullptr) {
            return CreateRCFailure;
        }

        // Share lists between threads.
        if (!wglShareLists( rc_, loading_rc_ )) {
            return ShareListsFailure;
        }

        // Set current contexts.
        if (!set_render_context( rc_ )) {
            return SetRCFailure;
        }

        // Create framebuffer objects.
        glGenFramebuffersEXT( 1, &fbo_ );

        // Show window.
        SetForegroundWindow( window_->get_handle() );
        SetFocus( window_->get_handle() );

        // Set scene up.
        setup_scene();
        return Success;
    }

    /*
     * Remove texture resources and contexts.
     */
    Graphics2D::ReturnStatus Graphics2D::clean_up( void )
    {
        // Empty texture map.
        for (auto i = textures_.begin(); i.has_next(); i.next()) {
            JUI::FileTexture* file_texture = i.get_value();
            JUTIL::BaseAllocator::destroy( file_texture );
        }
        textures_.clear();

        // Close rendering context.
        if (rc_ != nullptr) {
            // Unset contexts.
            if (!unset_render_context()) {
                return UnsetRCFailure;
            }

            // Delete rendering context.
            if (!wglDeleteContext( rc_ )) {
                return DeleteRCFailure;
            }

            rc_ = nullptr;
        }

        // Close loading rendering context.
        if (loading_rc_ != nullptr) {
            if (!wglDeleteContext( loading_rc_ )) {
                return DeleteRCFailure;
            }

            loading_rc_ = nullptr;
        }

        // Release device context.
        if (dc_ != nullptr) {
            if (ReleaseDC( window_->get_handle(), dc_ ) == 0) {
                return ReleaseDCFailure;
            }
        }

        return Success;
    }

    /*
     * Set rendering scene.
     */
    void Graphics2D::setup_scene( void )
    {
        // Set background colour.
        glClearColor( 0.16f, 0.15f, 0.145f, 1.0f );
        glDisable( GL_DEPTH_TEST );

        // Enable alpha blending.
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        // Enable 2D textures.
        glEnable( GL_TEXTURE_2D );

        // Set pixel storing alignment.
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

        // Enable vertical-sync.
        wglSwapIntervalEXT( 1 );
        
        // Size scene to window.
        resize_scene( window_->get_width(), window_->get_height() );
    }

    /*
     * Resize drawing scene.
     */
    void Graphics2D::resize_scene( GLsizei width, GLsizei height )
    {
        glViewport( 0, 0, width, height );

        // Set up orthographic projection.
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( -0.375f, width - 0.375f, height - 0.375f, -0.375f );

        // Set default model view.
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
    }

    /* 
     * Get texture by file name.
     */
    Graphics2D::ReturnStatus Graphics2D::get_texture( const JUTIL::String* filename, FileTexture** output )
    {
		// Stack for reporting.
		JUI::ErrorStack* stack = JUI::ErrorStack::get_instance();

        // Check if exists in map.
        FileTexture* texture;
        if (textures_.get( filename, &texture )) {
            *output = texture;
            return Success;
        }
        
        // Not found, load and insert.
        if (!JUTIL::BaseAllocator::allocate( &texture )) {
			stack->log( "Failed to allocate texture for %s!", filename->get_string() );
            return NoMemoryForTextureFailure;
        }
        texture = new (texture) FileTexture( filename );
        ReturnStatus error = load_texture( texture );
        if (error != Success) {
            JUTIL::BaseAllocator::destroy( texture );
            stack->log( "Failed to load texture %s.\n", filename->get_string() );
            return error;
        }

		// Add texture and return.
        if (!textures_.insert( filename, texture )) {
            JUTIL::BaseAllocator::destroy( texture );
            stack->log( "Failed to add texture to texture map." );
            return error;
		}
        *output = texture;
        return Success;
    }

    /*
     * Clear scene.
     */
    void Graphics2D::clear_scene( void )
    {
        glClear( GL_COLOR_BUFFER_BIT );
    }

    /*
     * Swap back buffers.
     */
    void Graphics2D::swap_buffers( void )
    {
        SwapBuffers( dc_ );
    }

    /*
     * Create texture from bitmap.
     */
    GLuint Graphics2D::create_texture( GLubyte* data, GLsizei width, GLsizei height, GLenum format )
    {
        // Create texture.
        GLuint texture;
        glGenTextures( 1, &texture );
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set texture filtering and wrap clamping.
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

        // Build mipmaps, delete buffer.
        glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data );
        glBindTexture( GL_TEXTURE_2D, 0 );
        return texture;
    }

    /*
     * Create empty texture.
     */
    Texture* Graphics2D::create_empty_texture( GLsizei width, GLsizei height, GLenum format )
    {
        // Stack for error logging.
        JUI::ErrorStack* stack = JUI::ErrorStack::get_instance();

        // Adjust size to be powers of 2.
        GLsizei real_width = OpenGLShared::next_power_of_2( width );
        GLsizei real_height = OpenGLShared::next_power_of_2( height );
        
        // Get component count.
        GLuint components;
        switch (format) {
        case GL_RGBA:
            components = 4;
            break;
        case GL_RGB:
            components = 3;
            break;
        case GL_LUMINANCE_ALPHA:
            components = 2;
            break;
        default:
            components = 1;
            break;
        }

        // Allocate and zero a buffer.
        JUTIL::ArrayBuilder<GLubyte> data;
        GLuint size = real_width * real_height * components;
        if (!data.set_size( size )) {
            return nullptr;
        }
        ZeroMemory( data.get_array(), size );

        // Calculate texture coordinates.
        float tu = static_cast<float>(width) / static_cast<float>(real_width);
        float tv = static_cast<float>(height) / static_cast<float>(real_height);

        // Create GL texture.
        GLuint texture = create_texture( data.get_array(), real_width, real_height, format );

        // Set texture and return.
        Texture* result;
        if (!JUTIL::BaseAllocator::allocate( &result )) {
            stack->log( "Failed to allocate texture object." );
            return false;
        }
        result = new (result) Texture( texture, width, height, tu, tv );
        return result;
    }

    /*
     * Load PNG texture from file.
     */
    Graphics2D::ReturnStatus Graphics2D::load_texture( FileTexture* file_texture )
    {
        // Get filename and URL.
        const JUTIL::String* filename = file_texture->get_filename();

        // Output variables.
        png_structp	png_ptr;
        png_infop	info_ptr;
        unsigned int sig_read = 0;
        
        // Attempt to open the file.
        FILE* fp = nullptr;
        errno_t error = fopen_s( &fp, filename->get_string(), "rb" );
        if (error != 0) {
            return OpenTextureFailure;
        }

        // Read PNG struct.
        png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr );
        if (png_ptr == nullptr) {
            fclose( fp );
            return ReadPNGFormatFailure;
        }

        // Create PNG info struct.
        info_ptr = png_create_info_struct( png_ptr );
        if (info_ptr == nullptr) {
            fclose( fp );
            png_destroy_read_struct( &png_ptr, nullptr, nullptr );
            return ReadPNGFormatFailure;
        }

        // Initialize I/O.
        png_init_io( png_ptr, fp );
        png_set_sig_bytes( png_ptr, sig_read );

        // Begin read.
        png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, nullptr );

        // Get size and allocate.
        png_uint_32 width = png_get_image_width( png_ptr, info_ptr );
        png_uint_32 height = png_get_image_height( png_ptr, info_ptr );
        png_uint_32 padded_width = OpenGLShared::next_power_of_2( width );
        png_uint_32 padded_height = OpenGLShared::next_power_of_2( height );
        unsigned int alloc_size = 4 * padded_width * padded_height;
		JUTIL::ArrayBuilder<GLubyte> buffer;
		if (!buffer.set_size( alloc_size )) {
            return NoMemoryForTextureFailure;
        }

        // Copy information.
        png_bytepp row_pointers = png_get_rows( png_ptr, info_ptr );
        for (png_uint_32 i = 0; i < height; ++i) {
            void* startPtr = buffer.get_array() + (4 * padded_width * i);
            memcpy( startPtr, row_pointers[i], 4 * width );	
        }

        // Clean up.
        png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
        fclose( fp );

        // Calculate texture coordinates.
        float tu = static_cast<float>(width) / static_cast<float>(padded_width);
        float tv = static_cast<float>(height) / static_cast<float>(padded_height);
        
        // Generate texture from data.
        GLuint texture = create_texture( buffer.get_array(), padded_width, padded_height, GL_RGBA );

        // Set texture.
        file_texture->set_texture( texture, width, height, tu, tv );
        return Success;
    }

    /*
     * Draw single pixel.
     */
    void Graphics2D::draw_pixel( int x, int y, const Colour& colour )
    {
        // Draw single pixel.
        glBegin( GL_POINTS );
        set_colour( colour );
        draw_vertex( x, y );
        glEnd();
    }

    /*
     * Draw rectangle.
     */
    void Graphics2D::draw_rectangle( int x, int y, int width, int height )
    {
        int x2 = x + width;
        int y2 = y + height;

        // Draw it.
        glBegin( GL_QUADS );
        draw_vertex( x, y );
        draw_vertex( x2, y );
        draw_vertex( x2, y2 );
        draw_vertex( x, y2 );
        glEnd();
    }

    /*
     * Draw rounded rectangle.
     */
    void Graphics2D::draw_rounded_rectangle( int x, int y, int width, int height, int radius )
    {
        // Segmentation constants.
        const float PI = 3.14159f;
        const unsigned int CORNER_SEGMENTS = 10;
        const float ANGLE_FRACTION = PI / static_cast<float>(CORNER_SEGMENTS);

        // Start triangle strip.
        push_matrix();
        translate( x, y );

        // Draw rounded corners.
        begin( GL_LINES );
        int iy;
        for (iy = 0; iy < radius; ++iy) {
            float fx = sqrt( static_cast<float>(radius*radius - iy*iy) );
            int ix = static_cast<int>(fx + 0.5f);

			// Get Y values.
			int top_y = (radius - 1) - iy;
			int bottom_y = (height - radius + iy);

            // Top.
            draw_vertex( radius - ix, top_y );
            draw_vertex( width - radius + ix, top_y );

            // Bottom.
            draw_vertex( radius - ix, bottom_y );
            draw_vertex( width - radius + ix, bottom_y );
        }

        // Draw box.
        end();
        draw_rectangle( 0, radius, width, height - (2 * radius) );
        pop_matrix();
    }

    /*
     * Sets vertices for a circle given a start and end radius.
     */
    void Graphics2D::draw_circle( int x, int y, int radius, GLfloat start_angle, GLfloat end_angle, unsigned int step_count ) const
    {
        // Draw all steps.
        for (unsigned int i = 0; i < step_count; i++) {
            float current_angle = start_angle + (end_angle - start_angle) * static_cast<float>(i) / static_cast<float>(step_count-1);

            // Draw vertex at position.
            float offset_x = static_cast<float>(radius) * sin( current_angle );
            float offset_y = -static_cast<float>(radius) * cos( current_angle );
            int vx = x + static_cast<int>(offset_x);
            int vy = y + static_cast<int>(offset_y);
            draw_vertex( vx, vy );
        }
    }

    /*
     * Draw texture to buffer.
     */
    void Graphics2D::draw_texture( const Texture* texture, int x, int y )
    {
        draw_texture( texture, x, y, texture->get_width(), texture->get_height() );
    }

    /*
     * Draw texture to buffer with size.
     */
    void Graphics2D::draw_texture( const Texture* texture, int x, int y, int width, int height )
    {
        // Set up end texture.
        int x2 = x + width;
        int y2 = y + height;

        // Set texture.
        glBindTexture( GL_TEXTURE_2D, texture->get_texture() );

        // Get texture coordinates.
        GLfloat tu = texture->get_tu();
        GLfloat tv = texture->get_tv();

        // Draw quad.
        begin( GL_QUADS );

        // Top left.
        glTexCoord2f( 0.0f, 0.0f );
        draw_vertex( x, y );

        // Top right.
        glTexCoord2f( tu, 0.0f );
        draw_vertex( x2, y );

        // Bottom right.
        glTexCoord2f( tu, tv );
        draw_vertex( x2, y2 );

        // Bottom left.
        glTexCoord2f( 0.0f, tv );
        draw_vertex( x, y2 );

        // End quad.
        glEnd();

        // Unbind texture.
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    /*
     * Run a display list.
     */
    void Graphics2D::draw_display_list( GLuint list, int x, int y )
    {
        // Draw at location.
        push_matrix();
        float fx = static_cast<float>(x);
        float fy = static_cast<float>(y);
        translate( x, y );
        glCallList( list );
        pop_matrix();
    }

    /*
     * Begin drawing a line loop.
     */
    void Graphics2D::begin( GLenum mode ) const
    {
        glBegin( mode );
    }

    /*
     * Add next vertex.
     */
    void Graphics2D::draw_vertex( int x, int y ) const
    {
        glVertex2i( x, y );
    }

    /*
     * Finish drawing.
     */
    void Graphics2D::end( void ) const
    {
        glEnd();
    }

    /*
     * Set translation state.
     */
    void Graphics2D::translate( int x, int y ) const
    {
        float fx = static_cast<float>(x);
        float fy = static_cast<float>(y);
        glTranslatef( fx, fy, 0.0f );
    }

    /*
     * Pushes a matrix onto the stack.
     */
    void Graphics2D::push_matrix( void ) const
    {
        glPushMatrix();
    }

    /*
     * Pops the matrix from the stack.
     */
    void Graphics2D::pop_matrix( void ) const
    {
        glPopMatrix();
    }

    /*
     * Get main render context.
     */
    HGLRC Graphics2D::get_render_context( void ) const
    {
        return rc_;
    }

    /*
     * Get loading context.
     */
    HGLRC Graphics2D::get_loading_context( void ) const
    {
        return loading_rc_;
    }

    /*
     * Set current thread's rendering context.
     */
    bool Graphics2D::set_render_context( HGLRC context )
    {
        return wglMakeCurrent( dc_, context ) != 0;
    }

    /*
     * Unset the thread's rendering context.
     */
    bool Graphics2D::unset_render_context( void )
    {
        return wglMakeCurrent( nullptr, nullptr ) != 0;
    }

    /*
     * Set the texture blend state.
     */
    void Graphics2D::set_blend_state( GLenum src_blend, GLenum dest_blend )
    {
        glBlendFunc( src_blend, dest_blend );
    }

    /*
     * Set drawn colour.
     */
    void Graphics2D::set_colour( const Colour& colour )
    {
        glColor4ub( colour.get_red(), colour.get_green(), colour.get_blue(), colour.get_alpha() );
    }

    /*
     * Set texture to be rendered to.
     */
    void Graphics2D::render_to_texture( const Texture* texture )
    {
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fbo_ );
        glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
            GL_TEXTURE_2D, texture->get_texture(), 0 );
        resize_scene( texture->get_width(), texture->get_height() );

        // Flip rendering for texture order.
        glMatrixMode( GL_PROJECTION );
        glScalef( 1.0f, -1.0f, 1.0f );
        translate( 0, -texture->get_height() );
        glMatrixMode( GL_MODELVIEW );
    }

    /*
     * Reset the render target.
     */
    void Graphics2D::reset_render_target( void )
    {
        // Unbind texture/buffer.
        glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0 );
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
        resize_scene( window_->get_width(), window_->get_height() );
    }

}
