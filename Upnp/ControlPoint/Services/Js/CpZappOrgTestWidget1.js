 

/**
 * Proxy for zapp.org:TestWidget:1
 */

var ServiceTestWidget = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/TestWidget/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestWidget";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["RegisterValue"] = new ServiceVariable("RegisterValue");
		this.iVariables["RegisterIndex"] = new ServiceVariable("RegisterIndex");
		this.iVariables["ReadWriteRegister0"] = new ServiceVariable("ReadWriteRegister0");
		this.iVariables["ReadWriteRegister1"] = new ServiceVariable("ReadWriteRegister1");
		this.iVariables["ReadWriteRegister2"] = new ServiceVariable("ReadWriteRegister2");
		this.iVariables["ReadWriteRegister3"] = new ServiceVariable("ReadWriteRegister3");
		this.iVariables["ReadOnlyRegister4"] = new ServiceVariable("ReadOnlyRegister4");
		this.iVariables["ReadOnlyRegister5"] = new ServiceVariable("ReadOnlyRegister5");
		this.iVariables["ReadOnlyRegister6"] = new ServiceVariable("ReadOnlyRegister6");
		this.iVariables["ReadOnlyRegister7"] = new ServiceVariable("ReadOnlyRegister7");
}


ServiceTestWidget.prototype.ServiceName = function(){
	return this.iType;
}

ServiceTestWidget.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestWidget.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceTestWidget.prototype.SetReadWriteRegister = function(RegisterIndex, RegisterValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetReadWriteRegister", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("RegisterIndex", RegisterIndex);
    request.WriteIntParameter("RegisterValue", RegisterValue);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


