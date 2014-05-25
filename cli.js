var net = require("net");
var socket = new net.Socket();
socket.setEncoding("utf8");

process.stdin.setEncoding('utf8');
process.stdin.setRawMode(true);

var soc = socket.connect(44, "169.254.1.1", function () {
	soc.on("data", function (data) {
		console.log(data);
	});
	soc.write("g");
	soc.write("h");
	setTimeout(function () {
		soc.write("n");
	}, 500);
	// soc.write("GET /?dir=w HTTP/1.1");
	// soc.write("\n\n");
});

process.stdin.on('data', function(key) {
	if (key === "\u0003") {
		process.exit();
	}
	else if (key == "g") {
		soc.write("g");
	}
	else if (key == "h") {
		soc.write("h");
	}
	else {
		soc.write("s");
	}
});

