#include "jui/gfx/freetype_font_manager.hpp"
#include "jui/gfx/freetype_font.hpp"

namespace JUI
{

    // Singleton handle.
    FreetypeFontManager* FreetypeFontManager::instance_ = nullptr;

    /*
     * Singleton instance getter/creator.
     */
    FreetypeFontManager* FreetypeFontManager::get_instance( void )
    {
        // Create instance.
        if (instance_ == nullptr) {
            // Allocate instance without exception.
            instance_ = (FreetypeFontManager*)malloc( sizeof(FreetypeFontManager) );
            if (instance_ != nullptr) {
                // Placement new and initialize.
                instance_ = new (instance_) FreetypeFontManager();
                if (!instance_->initialize()) {
                    return nullptr;
                }
            }
        }

        return instance_;
    }

    /*
     * Shut down Freetype manager.
     */
    void FreetypeFontManager::shut_down()
    {
        if (instance_ != nullptr) {
            delete instance_;
            instance_ = nullptr;
        }
    }

    /*
     * Create a font by filename and size.
     * Returns a font interface handle on success, nullptr otherwise.
     */
    FontInterface* FreetypeFontManager::create_font( const JUTIL::ConstantString& filename, unsigned int height )
    {
        // Create font.
        FT_Face face;
        FT_Error error = FT_New_Face( library_, filename.get_string(), 0, &face );

        // Fault and reload on fail.
        if (error != FT_Err_Ok) {
            return nullptr;
        }

        // Set character height.
        FT_Set_Char_Size( face, 0, height << 6, 96, 96 );

        // Create font.
        FontInterface* font = new FreetypeFont( face );
        fonts_.push( font );
        if (!font->initialize()) {
            return nullptr;
        }

        // Return face.
        FT_Done_Face( face );
        return font;
    }

    /*
     * Destroy a font.
     */
    void FreetypeFontManager::destroy_font( FontInterface* font )
    {
        // Find the font.
        fonts_.remove( font );
        font->release();
    }

    /*
     * Initialize Freetype.
     */
    bool FreetypeFontManager::initialize( void )
    {
        // Load library.
        FT_Error error = FT_Init_FreeType( &library_ );
        if (error != 0) {
            return false;
        }

        return true;
    }

    /*
     * Clean Freetype.
     */
    void FreetypeFontManager::close( void )
    {
        // Unload library.
        if (library_ != nullptr) {
            FT_Done_FreeType( library_ );
            library_ = nullptr;
        }
    }

    /*
     * Constructor.
     */
    FreetypeFontManager::FreetypeFontManager( void )
    {
        library_ = nullptr;
    }

    /*
     * Destructor.
     */
    FreetypeFontManager::~FreetypeFontManager( void )
    {
        close();
    }

}
