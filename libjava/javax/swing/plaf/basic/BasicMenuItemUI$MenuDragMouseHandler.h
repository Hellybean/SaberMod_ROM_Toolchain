
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicMenuItemUI$MenuDragMouseHandler__
#define __javax_swing_plaf_basic_BasicMenuItemUI$MenuDragMouseHandler__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace javax
  {
    namespace swing
    {
      namespace event
      {
          class MenuDragMouseEvent;
      }
      namespace plaf
      {
        namespace basic
        {
            class BasicMenuItemUI;
            class BasicMenuItemUI$MenuDragMouseHandler;
        }
      }
    }
  }
}

class javax::swing::plaf::basic::BasicMenuItemUI$MenuDragMouseHandler : public ::java::lang::Object
{

  BasicMenuItemUI$MenuDragMouseHandler(::javax::swing::plaf::basic::BasicMenuItemUI *);
public:
  virtual void menuDragMouseDragged(::javax::swing::event::MenuDragMouseEvent *);
  virtual void menuDragMouseEntered(::javax::swing::event::MenuDragMouseEvent *);
  virtual void menuDragMouseExited(::javax::swing::event::MenuDragMouseEvent *);
  virtual void menuDragMouseReleased(::javax::swing::event::MenuDragMouseEvent *);
public: // actually package-private
  BasicMenuItemUI$MenuDragMouseHandler(::javax::swing::plaf::basic::BasicMenuItemUI *, ::javax::swing::plaf::basic::BasicMenuItemUI$MenuDragMouseHandler *);
  ::javax::swing::plaf::basic::BasicMenuItemUI * __attribute__((aligned(__alignof__( ::java::lang::Object)))) this$0;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_plaf_basic_BasicMenuItemUI$MenuDragMouseHandler__
