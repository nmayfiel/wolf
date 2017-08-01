//
// mlx_int.h for minilibx
//
// ol@staff.42.fr
//
// include opengl needed before mlx_int.h
//

#import <Cocoa/Cocoa.h>
#import "mlx_int.h"

@interface NSWindowEvent : NSWindow
{
  func_t	event_funct[MAX_EVENT];
  void		*(event_param[MAX_EVENT]);
  int		keyrepeat;
  int		keyflag;
  int		size_x;
  int		size_y;
}
- (NSWindowEvent *) initWithContentRect:(NSRect)rect styleMask:(NSUInteger)winstyle backing:(NSBackingStoreType)bck defer:(BOOL) dfr;
- (void) setEvent:(int)event andFunc:(func_t)func andParam:(void *)param;
- (void) setKeyRepeat:(int)mode;
- (void) exposeNotification:(NSNotification *)note;
- (void) closeNotification:(NSNotification *)note;
@end


@interface MlxWin : NSOpenGLView
{
	NSWindowEvent		*win;
	NSOpenGLContext	*ctx;
	glsl_info_t		glsl;
	int			openglwin;
	
	int			size_x;
	int			size_y;
	
	int			pixel_nb;
	GLuint		pixel_vbuffer;
	GLuint		pixel_texture;
	unsigned int		*pixtexbuff;
}

- (id) initWithRect: (NSRect)rect andTitle: (NSString *)title pfaAttrs: (NSOpenGLPixelFormatAttribute *)attrs;
- (void) selectGLContext;
- (void) flushGLContext;
- (void) pixelPutColor: (int)color X:(int)x Y:(int)y;
- (void) mlx_gl_draw;
- (void) mlx_gl_draw_img:(mlx_img_list_t *)img andCtx:(mlx_img_ctx_t *)imgctx andX:(int)x andY:(int)y;
- (void) nix_gl_draw_img:(mlx_img_list_t *)img andCtx:(mlx_img_ctx_t *)imgctx andX:(int)x andY:(int)y andScale:(float[2])scale;
- (void) drawRect: (NSRect)bounds;
- (void) mlx_gl_draw_font:(mlx_img_list_t *)img andCtx:(mlx_img_ctx_t *)imgctx andX:(int)x andY:(int)y andColor:(int)color glyphX:(int)gx glyphY:(int)gy;
- (NSOpenGLContext *) ctx;
- (void) setEvent:(int)event andFunc:(func_t)func andParam:(void *)param;
- (void) setKeyRepeat:(int)mode;
- (void) ctxNeedsUpdate;
- (void) nx_mouse_set_cursor_association:(int) tf;
- (void) nx_display_cursor: (int) tf;
												     

@end
