/* array helper */
Array.prototype.remove = function(from, to) {
  var rest = this.slice((to || from) + 1 || this.length);
  this.length = from < 0 ? this.length + from : from;
  return this.push.apply(this, rest);
};

/* debug console */

if (typeof console == "undefined") {
    window["console"] = {"log":function(){}};
}

var debugEnabled = true;// /debug=true/i.test(location.search);

var debug = {
    log : function(message){
        if (debugEnabled){
            var debugCallback = window["debugccallback"];
            if (debugCallback){
                debugCallback(message);
            }
        }
        console.log(message);
    },
    stop: function(){
        debugEnabled = false;
    },
    start: function(){
        debugEnabled = true;
    }
}

/* OOP Helper */
Function.prototype.inheritsFrom = function( parentClassOrObject ){ 
	if ( parentClassOrObject.constructor == Function ) 
	{ 
		//Normal Inheritance 
		this.prototype = new parentClassOrObject;
		this.prototype.constructor = this;
		this.prototype.superclass = parentClassOrObject.prototype;
	} 
	else 
	{ 
		//Pure Virtual Inheritance 
		this.prototype = parentClassOrObject;
		this.prototype.constructor = this;
		this.prototype.superclass = parentClassOrObject;
	} 
	return this;
} 

/* base64 decoding */

 var keyStr = "ABCDEFGHIJKLMNOP" +
               "QRSTUVWXYZabcdef" +
               "ghijklmnopqrstuv" +
               "wxyz0123456789+/" +
               "=";

  function decode64(input) {
	 var result = [];
	 if (input && input.length){
		 var output = [];
		 var chr1, chr2, chr3 = "";
		 var enc1, enc2, enc3, enc4 = "";
		 var i = 0;

		 // remove all characters that are not A-Z, a-z, 0-9, +, /, or =
		 var base64test = /[^A-Za-z0-9\+\/\=]/g;
		 if (base64test.exec(input)) {
			alert("There were invalid base64 characters in the input text.\n" +
				  "Valid base64 characters are A-Z, a-z, 0-9, '+', '/',and '='\n" +
				  "Expect errors in decoding.");
		 }
		 input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");

		 do {
			enc1 = keyStr.indexOf(input.charAt(i++));
			enc2 = keyStr.indexOf(input.charAt(i++));
			enc3 = keyStr.indexOf(input.charAt(i++));
			enc4 = keyStr.indexOf(input.charAt(i++));

			chr1 = (enc1 << 2) | (enc2 >> 4);
			chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
			chr3 = ((enc3 & 3) << 6) | enc4;

			output[output.length] = chr1;

			if (enc3 != 64) {
			output[output.length] = chr2;
			}
			if (enc4 != 64) {
			output[output.length] = chr3;
			}

			chr1 = chr2 = chr3 = "";
			enc1 = enc2 = enc3 = enc4 = "";

		 } while (i < input.length);

		 var j=0;
		 for (var i = 0; i < output.length; i += 4, ++j){
			result[j] = getUIntAt(output, i);
		 }
	 }
	 return result;
  }
  
 function getUIntAt ( arr, offs ) {
	return (arr[offs+0] << 24) +
	(arr[offs+1] << 16) +
	(arr[offs+2] << 8) +
	arr[offs+3] >>> 0;
}
			 