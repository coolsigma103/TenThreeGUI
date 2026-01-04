from TTGUI import Application, Frame, maths
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
app.run()