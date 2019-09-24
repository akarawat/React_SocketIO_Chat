#เชื่อมต่อก่อน
import socketio
sio = socketio.Client()
sio.connect('http://34.87.86.224:3001')

#ถ้าจะส่ง
@sio.on('connect')
def on_connect():
    print("connection established")
#sio.emit('emit', {'count':1})

#ถ้าจะรับ
@sio.on('count') #<< Emit ที่ส่งมา
def on_message(data):
    print('message received with ', data)

#เสร็จแล้วปิด
@sio.on('disconnect')
def on_disconnect():
    print('disconnected from server')

#รอทุกครั้ง    
sio.wait()
