from TTGUI import Application, Frame, assets, maths, Panel
import os

print(os.getpid())

app = Application()

frame1 = Frame(app, size = maths.Vector2(500, 600))

def resizecallbacktest(frame, size):
    print(f"{frame.getTitle()} size: {size.x}, {size.y}")
def closecallbacktest(frame):
    print(f"{frame.getTitle()} closed")
def focuscallbacktest(frame, focus):
    print(f"{frame.getTitle()} {"focus" if focus else "unfocus"}")

frame1.setResizeCallback(resizecallbacktest)
frame1.setCloseCallback(closecallbacktest)
frame1.setFocusCallback(focuscallbacktest)

icon1 = assets.Image("./test_res/example.jpg")
frame1.setIcon(icon1)

frame1.setBgColor(assets.Color(255.0, 0.0, 0.0))

panel = Panel()
panel.size = maths.Vector2(10, 10);panel.position = maths.Vector2(50, 50)
panel.color = assets.Color(255, 255, 0, 1)

frame1.addComponent(panel)

print(assets.Color(255.0,255.0,0.0,0.0))
app.run()