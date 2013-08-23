#include "jui/gfx/freetype_font_manager.hpp"
#include "jui/gfx/freetype_font.hpp"
#include "jui/application/error_stack.hpp"

namespace JUI
{

	// Singleton handle.
	FreetypeFontManager* FreetypeFontManager::instance_ = nullptr;

	/*
	 * Singleton instance getter/creator.
	 */
	FreetypeFontManager* FreetypeFontManager::get_instance( void )
	{
		// Create instance if missing.
		if (instance_ == nullptr) {
			// Allocate instance.
			FreetypeFontManager* instance;
			if (!JUTIL::BaseAllocator::allocate( &instance )) {
				return nullptr;
			}

			// Initialize manager.
			instance = new (instance) FreetypeFontManager();
			if (!instance->initialize()) {
				return nullptr;
			}
			instance_ = instance;
		}

		return instance_;
	}

	/*
	 * Shut down Freetype manager.
	 */
	void FreetypeFontManager::shut_down( void )
	{
		JUTIL::BaseAllocator::safe_destroy( &instance_ );
	}

	/*
	 * Create a font by filename and size.
	 * Returns a font interface handle on success, nullptr otherwise.
	 */
	FontInterface* FreetypeFontManager::create_font( const JUTIL::String* filename, unsigned int height )
	{
		// Create font.
		FT_Face face;
		FT_Error error = FT_New_Face( library_, filename->get_string(), 0, &face );
		JUI::ErrorStack* stack = JUI::ErrorStack::get_instance();
		if (error != FT_Err_Ok) {
			stack->log( "Failed to create font from file: %s!", filename->get_string() );
			return nullptr;
		}

		// Set character height.
		FT_Set_Char_Size( face, height << 6, height << 6, 96, 96 );

		// Create font.
		FreetypeFont* font;
		if (!JUTIL::BaseAllocator::allocate( &font )) {
			stack->log( "Failed to allocate font." );
			return nullptr;
		}
		font = new (font) FreetypeFont( face );

		// Add and initialize font.
		FontInterface* font_interface = static_cast<FontInterface*>(font);
		if (!fonts_.push( font_interface )) {
			JUTIL::BaseAllocator::destroy( font );
			stack->log( "Failed to add font to interface." );
			return nullptr;
		}
		if (!font_interface->initialize()) {
			return nullptr;
		}

		// Return face.
		FT_Done_Face( face );
		return font_interface;
	}

	/*
	 * Destroy a font.
	 */
	void FreetypeFontManager::destroy_font( FontInterface* font )
	{
		// Find the font.
		if (font != nullptr) {
			fonts_.remove( font );
			font->release();
		}
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
