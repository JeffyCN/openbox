// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-

#ifdef    HAVE_CONFIG_H
#  include "../config.h"
#endif // HAVE_CONFIG_H

#include "renderstyle.hh"
#include "display.hh"
#include "screeninfo.hh"

namespace otk {

RenderStyle::RenderStyle(int screen, const std::string &stylefile)
  : _screen(screen),
    _file(stylefile)
{
  _text_color_focus = new RenderColor(_screen, 0x272a2f);
  _text_color_unfocus = new RenderColor(_screen, 0x676869);

  _button_color_focus = new RenderColor(_screen, 0x96ba86);
  _button_color_unfocus = new RenderColor(_screen, 0x676869);

  _frame_border_color = new RenderColor(_screen, 0x181f24);
  _frame_border_width = 1;

  _client_border_color_focus = new RenderColor(_screen, 0x858687);
  _client_border_color_unfocus = new RenderColor(_screen, 0x555657);
  _client_border_width = 1;

  _titlebar_focus = new RenderTexture(_screen,
                                      false,
                                      RenderTexture::Flat,
                                      RenderTexture::Bevel1,
                                      false,
                                      RenderTexture::Vertical,
                                      false,
                                      0x858687,
                                      0x373a3f,
                                      0x0,
                                      0x0);
  _titlebar_unfocus = new RenderTexture(_screen,
                                        false,
                                        RenderTexture::Flat,
                                        RenderTexture::Bevel1,
                                        false,
                                        RenderTexture::Vertical,
                                        false,
                                        0x555657,
                                        0x171a1f,
                                        0x0,
                                        0x0);

  _label_focus = new RenderTexture(_screen,
                                   false,
                                   RenderTexture::Flat,
                                   RenderTexture::Bevel1,
                                   true,
                                   RenderTexture::Vertical,
                                   false,
                                   0x858687,
                                   0x373a3f,
                                   0x181f24,
                                   0x0);
  _label_unfocus = new RenderTexture(_screen,
                                     false,
                                     RenderTexture::Sunken,
                                     RenderTexture::Bevel1,
                                     false,
                                     RenderTexture::CrossDiagonal,
                                     false,
                                     0x555657,
                                     0x272a2f,
                                     0x0,
                                     0x0);


  _handle_focus = new RenderTexture(_screen,
                                    false,
                                    RenderTexture::Flat,
                                    RenderTexture::Bevel1,
                                    true,
                                    RenderTexture::Vertical,
                                    false,
                                    0x858687,
                                    0x373a3f,
                                    0x0,
                                    0x0);
  _handle_unfocus = new RenderTexture(_screen,
                                      false,
                                      RenderTexture::Flat,
                                      RenderTexture::Bevel1,
                                      false,
                                      RenderTexture::Vertical,
                                      false,
                                      0x555657,
                                      0x171a1f,
                                      0x0,
                                      0x0);

  
  _button_unpress_focus = new RenderTexture(_screen,
                                            false,
                                            RenderTexture::Raised,
                                            RenderTexture::Bevel2,
                                            false,
                                            RenderTexture::CrossDiagonal,
                                            false,
                                            0x858687,
                                            0x272a2f,
                                            0x0,
                                            0x0);
  _button_unpress_unfocus = new RenderTexture(_screen,
                                              false,
                                              RenderTexture::Raised,
                                              RenderTexture::Bevel2,
                                              false,
                                              RenderTexture::CrossDiagonal,
                                              false,
                                              0x555657,
                                              0x171a1f,
                                              0x0,
                                              0x0);

  _button_press_focus = new RenderTexture(_screen,
                                          false,
                                          RenderTexture::Sunken,
                                          RenderTexture::Bevel2,
                                          false,
                                          RenderTexture::CrossDiagonal,
                                          false,
                                          0x96ba86,
                                          0x5a724c,
                                          0x0,
                                          0x0);
  _button_press_unfocus = new RenderTexture(_screen,
                                            false,
                                            RenderTexture::Sunken,
                                            RenderTexture::Bevel2,
                                            false,
                                            RenderTexture::CrossDiagonal,
                                            false,
                                            0x555657,
                                            0x171a1f,
                                            0x0,
                                            0x0);

  _grip_focus = new RenderTexture(_screen,
                                  false,
                                  RenderTexture::Flat,
                                  RenderTexture::Bevel1,
                                  false,
                                  RenderTexture::Vertical,
                                  false,
                                  0x96ba86,
                                  0x5a724c,
                                  0x0,
                                  0x0);
  _grip_unfocus = new RenderTexture(_screen,
                                    false,
                                    RenderTexture::Flat,
                                    RenderTexture::Bevel1,
                                    false,
                                    RenderTexture::Vertical,
                                    false,
                                    0x555657,
                                    0x171a1f,
                                    0x0,
                                    0x0);

  _label_font = new Font(_screen, "Arial,Sans-9:bold", true, 1, 0x40);

  XImage *image = XCreateImage(**display,
                               display->screenInfo(_screen)->visual(),
                               2, XYBitmap, 0, NULL, 8, 8, 0, 0);
  assert(image);
  
  _max_mask = new PixmapMask();
  _max_mask->w = _max_mask->h = 8;
  {
    unsigned char data[] = {
      0,1,1,1,1,1,1,0,
      1,1,1,1,1,1,1,1,
      1,1,0,0,0,0,1,1,
      1,1,0,0,0,0,1,1,
      1,1,0,0,0,0,1,1,
      1,1,0,0,0,0,1,1,
      1,1,1,1,1,1,1,1,
      0,1,1,1,1,1,1,0 };
    image->data = (char*)data;
    XPutImage(**display, _max_mask->mask, DefaultGC(**display, _screen),
              image, 0, 0, 0, 0, 8, 8);
  }

  _icon_mask = new PixmapMask();
  _icon_mask->w = _icon_mask->h = 8;
  {
    unsigned char data[] = {
      0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,
      1,1,0,0,0,0,1,1,
      1,1,1,0,0,1,1,1,
      0,1,1,1,1,1,1,0,
      0,0,1,1,1,1,0,0,
      0,0,0,1,1,0,0,0,
      0,0,0,0,0,0,0,0 };
    image->data = (char*)data;
    XPutImage(**display, _icon_mask->mask, DefaultGC(**display, _screen),
              image, 0, 0, 0, 0, 8, 8);
  }
  
  _stick_mask = new PixmapMask();
  _stick_mask->w = _stick_mask->h = 8;
  {
    unsigned char data[] = {
      0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,
      0,0,0,1,1,0,0,0,
      0,0,1,1,1,1,0,0,
      0,0,1,1,1,1,0,0,
      0,0,0,1,1,0,0,0,
      0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0 };    
    image->data = (char*)data;
    XPutImage(**display, _stick_mask->mask, DefaultGC(**display, _screen),
              image, 0, 0, 0, 0, 8, 8);
  }
  
  _close_mask = new PixmapMask();
  _close_mask->w = _close_mask->h = 8;
  {
    unsigned char data[] = {
      1,1,0,0,0,0,1,1,
      1,1,1,0,0,1,1,1,
      0,1,1,1,1,1,1,0,
      0,0,1,1,1,1,0,0,
      0,0,1,1,1,1,0,0,
      0,1,1,1,1,1,1,0,
      1,1,1,0,0,1,1,1,
      1,1,0,0,0,0,1,1 };
    image->data = (char*)data;
    XPutImage(**display, _close_mask->mask, DefaultGC(**display, _screen),
              image, 0, 0, 0, 0, 8, 8);
  }

  image->data = NULL;
  XDestroyImage(image);
}

RenderStyle::~RenderStyle()
{
  delete _text_color_focus;
  delete _text_color_unfocus;

  delete _button_color_focus;
  delete _button_color_unfocus;

  delete _frame_border_color;

  delete _client_border_color_focus; 
  delete _client_border_color_unfocus;
 
  delete _titlebar_focus;
  delete _titlebar_unfocus;

  delete _label_focus;
  delete _label_unfocus;

  delete _handle_focus;
  delete _handle_unfocus;

  delete _button_unpress_focus;
  delete _button_unpress_unfocus;
  delete _button_press_focus;
  delete _button_press_unfocus;

  delete _grip_focus;
  delete _grip_unfocus;

  delete _label_font;

  delete _max_mask;
  delete _icon_mask;
  delete _stick_mask;
  delete _close_mask;
}

}
