#include "jui/freetype_font_manager.h"
#include "jui/freetype_font.h"

// Singleton handle.
FreetypeFontManager* FreetypeFontManager::instance_ = nullptr;

/*
 * Singleton instance getter/creator.
 */
FreetypeFontManager* FreetypeFontManager::get_instance()
{
	// Create instance.
	if (instance_ == nullptr) {
		instance_ = new FreetypeFontManager();
		instance_->initialize();
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
 */
IFont* FreetypeFontManager::create_font( const std::string& filename, unsigned int height )
{
	// Create font.
	FT_Face face;
	FT_Error error = FT_New_Face( library_, filename.c_str(), 0, &face );

	// Fault and reload on fail.
	if (error != FT_Err_Ok) {
		throw std::runtime_error( "Failed to load font: " + filename + "!" );
	}

	// Set character height.
	FT_Set_Char_Size( face, 0, height << 6, 96, 96 );

	// Create font.
	FreetypeFont* font = new FreetypeFont( face );
	font->generate_glyphs();

	// Add to set to destroy.
	fonts_.push_back( font );

	// Return face.
	FT_Done_Face( face );
	return font;
}

/*
 * Destroy a font.
 */
void FreetypeFontManager::destroy_font( IFont* font )
{
	// Find the font.
	for (auto i = fonts_.begin(); i != fonts_.end(); i++) {
		FreetypeFont* current = *i;

		// Delete font if found.
		if (current == font ) {
			fonts_.erase( i );
			delete current;
			break;
		}
	}
}

/*
 * Initialize Freetype.
 */
void FreetypeFontManager::initialize()
{
	// Load library.
	FT_Error error = FT_Init_FreeType( &library_ );
	if (error != 0) {
		throw std::runtime_error( "Failed to initialize FreeType library." );
	}
}

/*
 * Clean Freetype.
 */
void FreetypeFontManager::close()
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
FreetypeFontManager::FreetypeFontManager()
{
	library_ = nullptr;
}

/*
 * Destructor.
 */
FreetypeFontManager::~FreetypeFontManager()
{
	close();
}