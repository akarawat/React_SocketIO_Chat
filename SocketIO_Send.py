#เชื่อมต่อก่อน
import socketio
sio = socketio.Client()
sio.connect('http://34.87.86.224:3002')

#ถ้าจะส่ง
@sio.on('connect')
def on_connect():
    print("connection established")
sio.emit('servo', {'pulse':88})

#เสร็จแล้วปิด
@sio.on('disconnect')
def on_disconnect():
    print('disconnected from server')

#รอทุกครั้ง    
sio.wait()


