module LibFunctions_15118_3 {
group generalFunctions {
type record ListOfFloat {
record length (0 .. 10) of float v_float
}
type record ListOfBoolean {
record length (0 .. 10) of boolean v_boolean
}
external function fx_logToFile(in template ListOfFloat v_listOfFloat,
in template ListOfBoolean v_listOfBoolean);
external function fx_generateNID(hexstring nmk) return hexstring;
external function fx_captureTraffic(in integer v_interfaceIdx);
external function fx_stopCapturing();
function f_randomHexStringGen(integer hexLength) return hexstring {
var hexstring randomHex := ''H;
for (var integer i:=0; i<hexLength/2; i:=i + 1) {
var float rndFloat := -1.0;
while(rndFloat<0.0 or rndFloat>255.0){
rndFloat := rnd(rnd());
rndFloat := rndFloat*10E2;
}
var hexstring randomHexByte := int2hex(float2int(rndFloat),2);
randomHex := randomHex & randomHexByte;
}
return randomHex;
}
function sleep(float time) {
timer t := time;
t.start;
t.timeout;
}
}
}