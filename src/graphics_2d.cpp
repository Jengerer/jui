#include "jui/graphics_2d.h"
#include <png.h>

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
void Graphics2D::initialize( void )
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
		throw std::runtime_error( "Failed to get device context for window." );
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
			throw std::runtime_error( "Failed to set fullscreen mode." );
		}
	}

	// Choose pixel format.
	GLuint pixelFormat = ChoosePixelFormat( dc_, &pixelDesc );
	if (pixelFormat == 0) {
		throw std::runtime_error( "Failed to choose pixel format." );
	}

	// Set received pixel format.
	if (!SetPixelFormat( dc_, pixelFormat, &pixelDesc )) {
		throw std::runtime_error( "Failed to set pixel format." );
	}

	// Create GLRC handle.
	rc_ = wglCreateContext( dc_ );
	if (rc_ == nullptr) {
		throw std::runtime_error( "Failed to create OpenGL context." );
	}

	// Creating loading GLRC handle.
	loading_rc_ = wglCreateContext( dc_ );
	if (loading_rc_ == nullptr) {
		throw std::runtime_error( "Failed to create loading OpenGL context." );
	}

	// Share lists between threads.
	if (!wglShareLists( rc_, loading_rc_ )) {
		throw std::runtime_error( "Failed to share lists between contexts." );
	}

	// Set current contexts.
	if (!set_render_context( rc_ )) {
		throw std::runtime_error( "Failed to set current context." );
	}

	// Create framebuffer objects.
	glGenFramebuffersEXT( 1, &fbo_ );

	// Show window.
	SetForegroundWindow( window_->get_handle() );
	SetFocus( window_->get_handle() );

	// Set scene up.
	setup_scene();
}

/*
 * Remove texture resources and contexts.
 */
void Graphics2D::clean_up()
{
	// Empty texture map.
	for (auto i = textures_.begin(); i != textures_.end(); i = textures_.erase( i )) {
		delete i->second;
	}

	// Close rendering context.
	if (rc_ != nullptr) {
		// Unset contexts.
		if (!unset_render_context()) {
			throw std::runtime_error( "Release of device and render context failed." );
		}

		// Delete rendering context.
		if (!wglDeleteContext( rc_ )) {
			throw std::runtime_error( "Releasing render context failed." );
		}

		rc_ = nullptr;
	}

	// Close loading rendering context.
	if (loading_rc_ != nullptr) {
		if (!wglDeleteContext( loading_rc_ )) {
			throw std::runtime_error( "Failed to release load render context." );
		}

		loading_rc_ = nullptr;
	}

	// Release device context.
	if (dc_ != nullptr) {
		if (ReleaseDC( window_->get_handle(), dc_ ) == 0) {
			throw std::runtime_error( "Failed to release device context." );
		}
	}
}

/*
 * Set rendering scene.
 */
void Graphics2D::setup_scene()
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

	// Flat shading.
	glEnable( GL_POLYGON_SMOOTH );
	glEnable( GL_LINE_SMOOTH );
	glShadeModel( GL_SMOOTH );
	
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
	gluOrtho2D( 0.0f, width, height, 0.0f );

	// Set default model view.
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

/* 
 * Get texture by file name.
 */
FileTexture* Graphics2D::get_texture( const std::string& filename )
{
	// Check if exists in map.
	auto i = textures_.find( filename );
	if (i != textures_.end()) {
		return i->second;
	}
	
	// Not found, load and insert.
	FileTexture* result = new FileTexture( filename );
	textures_[filename] = result;

	// NOTE: Inserted into table before load so cleanup works.
	load_texture( result );
	return result;
}

/*
 * Clear scene.
 */
void Graphics2D::clear_scene()
{
	glClear( GL_COLOR_BUFFER_BIT );
}

/*
 * Swap back buffers.
 */
void Graphics2D::swap_buffers()
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
	// Adjust size to be powers of 2.
	GLsizei real_width = next_power_of_2( width );
	GLsizei real_height = next_power_of_2( height );
	
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
	GLuint size = real_width * real_height * components;
	GLubyte* data = new GLubyte[size];
	ZeroMemory( data, size );

	// Calculate texture coordinates.
	float tu = static_cast<float>(width) / static_cast<float>(real_width);
	float tv = static_cast<float>(height) / static_cast<float>(real_height);

	// Create GL texture.
	GLuint texture = create_texture( data, real_width, real_height, format );
	delete[] data;

	// Set texture and return.
	Texture* result = new Texture( texture, width, height, tu, tv );
	return result;
}

/*
 * Load PNG texture from file.
 */
void Graphics2D::load_texture( FileTexture* file_texture )
{
	// Get filename and URL.
	const std::string& filename = file_texture->get_filename();

	// Output variables.
	png_structp	png_ptr;
	png_infop	info_ptr;
	unsigned int sig_read = 0;
	
	// Attempt to open the file.
	FILE* fp = nullptr;
	errno_t error = fopen_s( &fp, filename.c_str(), "rb" );
	if (error != 0) {
		throw std::runtime_error( "Failed to open texture file: " + filename + "!" );
	}

	// Read PNG struct.
	png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr );
	if (png_ptr == nullptr) {
		fclose( fp );
		throw std::runtime_error( "Failed to create PNG read struct." );
	}

	// Create PNG info struct.
	info_ptr = png_create_info_struct( png_ptr );
	if (info_ptr == nullptr) {
		fclose( fp );
		png_destroy_read_struct( &png_ptr, nullptr, nullptr );
		throw std::runtime_error( "Failed to create PNG info struct." );
	}

	// Initialize I/O.
	png_init_io( png_ptr, fp );
	png_set_sig_bytes( png_ptr, sig_read );

	// Begin read.
	png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, nullptr );

	// Get size and allocate.
	png_uint_32 width = png_get_image_width( png_ptr, info_ptr );
	png_uint_32 height = png_get_image_height( png_ptr, info_ptr );
	png_uint_32 padded_width = next_power_of_2( width );
	png_uint_32 padded_height = next_power_of_2( height );
	unsigned int allocSize = 4 * padded_width * padded_height;
	GLubyte* output = new GLubyte[ allocSize ];
	if (output == nullptr) {
		throw std::runtime_error( "Failed to allocate memory for PNG image." );
	}

	// Copy information.
	png_bytepp row_pointers = png_get_rows( png_ptr, info_ptr );
	for (png_uint_32 i = 0; i < height; ++i) {
		void* startPtr = output + (4 * padded_width * i);
		memcpy( startPtr, row_pointers[i], 4 * width );	
	}

	// Clean up.
	png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
	fclose( fp );

	// Calculate texture coordinates.
	float tu = static_cast<float>(width) / static_cast<float>(padded_width);
	float tv = static_cast<float>(height) / static_cast<float>(padded_height);
	
	// Generate texture from data.
	GLuint texture = create_texture( output, padded_width, padded_height, GL_RGBA );
	delete[] output;

	// Set texture.
	file_texture->set_texture( texture, width, height, tu, tv );
}

/*
 * Draw single pixel.
 */
void Graphics2D::draw_pixel( GLfloat x, GLfloat y, const Colour& colour )
{
	// Draw single pixel.
	glBegin( GL_POINTS );
	set_colour( colour );
	this->draw_vertex( x, y );
	glEnd();
}

/*
 * Draw rectangle.
 */
void Graphics2D::draw_rectangle( GLfloat x, GLfloat y, GLfloat width, GLfloat height )
{
	GLfloat x2 = x + width;
	GLfloat y2 = y + height;

	// Draw it.
	glBegin( GL_QUADS );
	glVertex2f( x, y );
	glVertex2f( x2, y );
	glVertex2f( x2, y2 );
	glVertex2f( x, y2 );
	glEnd();
}

/*
 * Draw rounded rectangle.
 */
void Graphics2D::draw_rounded_rectangle( GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat radius )
{
	// Segmentation constants.
	const float PI = 3.14159f;
	const unsigned int CORNER_SEGMENTS = 10;
	const float ANGLE_FRACTION = PI / static_cast<float>(CORNER_SEGMENTS);

	// Start triangle strip.
	push_matrix();
	translate( x, y );
	glBegin( GL_TRIANGLE_FAN );

	// Top left corner.
	set_colour( Colour( 255, 255, 255, 255 ) );
	draw_circle( radius, radius, radius, 1.5f * PI, 2.0f * PI, CORNER_SEGMENTS );
	draw_circle( width - radius, radius, radius, 0, 0.5f * PI, CORNER_SEGMENTS );
	draw_circle( width - radius, height - radius, radius, 0.5f * PI, PI, CORNER_SEGMENTS );
	draw_circle( radius, height - radius, radius, PI, 1.5f * PI, CORNER_SEGMENTS );
	end();
	pop_matrix();
}

/*
 * Sets vertices for a circle given a start and end radius.
 */
void Graphics2D::draw_circle( GLfloat x, GLfloat y, GLfloat radius, GLfloat start_angle, GLfloat end_angle, unsigned int step_count ) const
{
	// Draw all steps.
	for (unsigned int i = 0; i < step_count; i++) {
		float current_angle = start_angle + (end_angle - start_angle) * static_cast<float>(i) / static_cast<float>(step_count-1);
		draw_vertex( x + radius * sin( current_angle ), y - radius * cos( current_angle ) );
	}
}

/*
 * Draw texture to buffer.
 */
void Graphics2D::draw_texture( const Texture* texture, GLfloat x, GLfloat y )
{
	draw_texture( texture, x, y, texture->get_width(), texture->get_height() );
}

/*
 * Draw texture to buffer with size.
 */
void Graphics2D::draw_texture( const Texture* texture, GLfloat x, GLfloat y, GLsizei width, GLsizei height )
{
	// Set up end texture.
	GLfloat x2 = x + width;
	GLfloat y2 = y + height;

	// Set texture.
	glBindTexture( GL_TEXTURE_2D, texture->get_texture() );

	// Get texture coordinates.
	GLfloat tu = texture->get_tu();
	GLfloat tv = texture->get_tv();

	// Draw quad.
	glBegin( GL_QUADS );
		glTexCoord2f( 0.0f, 0.0f ); glVertex2f( x, y );
		glTexCoord2f( tu, 0.0f ); glVertex2f( x2, y );
		glTexCoord2f( tu, tv );	glVertex2f( x2, y2 );
		glTexCoord2f( 0.0f, tv ); glVertex2f( x, y2 );
	glEnd();

	// Unbind texture.
	glBindTexture( GL_TEXTURE_2D, 0 );
}

/*
 * Run a display list.
 */
void Graphics2D::draw_display_list( GLuint list, GLfloat x, GLfloat y )
{
	glPushMatrix();
	glTranslatef( x, y, 0.0f );
	glCallList( list );
	glPopMatrix();
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
void Graphics2D::draw_vertex( float x, float y ) const
{
	glVertex2f( x, y );
}

/*
 * Finish drawing.
 */
void Graphics2D::end() const
{
	glEnd();
}

/*
 * Set translation state.
 */
void Graphics2D::translate( float x, float y ) const
{
	glTranslatef( x, y, 0.0f );
}

/*
 * Pushes a matrix onto the stack.
 */
void Graphics2D::push_matrix() const
{
	glPushMatrix();
}

/*
 * Pops the matrix from the stack.
 */
void Graphics2D::pop_matrix() const
{
	glPopMatrix();
}

/*
 * Get main render context.
 */
HGLRC Graphics2D::get_render_context() const
{
	return rc_;
}

/*
 * Get loading context.
 */
HGLRC Graphics2D::get_loading_context() const
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
bool Graphics2D::unset_render_context()
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
	glColor4ub( colour.r, colour.g, colour.b, colour.a );
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
	glTranslatef( 0.0f, static_cast<GLfloat>(-texture->get_height()),0.0f );
	glMatrixMode( GL_MODELVIEW );
}

/*
 * Reset the render target.
 */
void Graphics2D::reset_render_target()
{
	// Unbind texture/buffer.
	glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0 );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	resize_scene( window_->get_width(), window_->get_height() );
}