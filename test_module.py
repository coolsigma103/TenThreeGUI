from TTGUI import *
import os

print(os.getpid())

app = Application()

frame1 = Frame(app, size = maths.Vector2(500, 600), title = "frame1")
frame2 = Frame(app, maths.Vector2(200, 300))

frame2.setTitle("frame2")

def resizecallbacktest(frame, size):
    print(f"{frame.getTitle()} size: {size.x}, {size.y}")
def closecallbacktest(frame):
    print(f"{frame.getTitle()} closed")
def focuscallbacktest(frame, focus):
    print(f"{frame.getTitle()} {"focus" if focus else "unfocus"}")

frame1.setResizeCallback(resizecallbacktest)
frame2.setResizeCallback(resizecallbacktest)
frame1.setCloseCallback(closecallbacktest)
frame2.setCloseCallback(closecallbacktest)
frame1.setFocusCallback(focuscallbacktest)
frame2.setFocusCallback(focuscallbacktest)

icon1 = assets.Image("./test_res/example.jpg")
frame1.setIcon(icon1)

frame1.setBgColor(assets.Color(255.0, 0.0, 0.0))

panel = Panel()
panel.size.x = 20
panel.size.y = 20

frame1.addComponent(panel)

print(assets.Color(255.0,255.0,0.0,0.0))
app.run()