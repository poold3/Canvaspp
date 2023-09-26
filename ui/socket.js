const INPUT_CODES = {
  NONE: 0,
  DIMENSIONS: 1,
  MOUSE_POSITION: 2
}

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let socket = null;

function sendToServer(object) {
  if (socket != null && socket.readyState == 1) {
    socket.send(JSON.stringify(object));
  }
}

function handleWebSocketMessage(event) {
  console.log('Message from server:', event.data);
  eval(event.data);
}

function adjustCanvasSize() {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
  if (socket != null && socket.readyState == 1) {
    dimensions = {
      "code": INPUT_CODES.DIMENSIONS,
      "width": canvas.width,
      "height": canvas.height
    }
    sendToServer(dimensions);
  }
}

window.addEventListener("resize", adjustCanvasSize);

function connectWebSocket() {
  socket = new WebSocket("ws://localhost:65000");

  socket.addEventListener('open', (event) => {
    console.log('WebSocket connection opened:', event);

    socket.addEventListener('message', handleWebSocketMessage);

    adjustCanvasSize();
  });

  socket.addEventListener('close', (event) => {
    console.log('WebSocket connection closed:', event);
    socket.removeEventListener('message', handleWebSocketMessage);
    socket = null;
    window.close();
  });

  socket.addEventListener('error', (event) => {
    console.error('WebSocket error:', event);
  });
}

connectWebSocket();
