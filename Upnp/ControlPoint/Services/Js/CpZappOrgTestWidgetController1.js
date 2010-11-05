 

/**
 * Proxy for zapp.org:TestWidgetController:1
 */

var ServiceTestWidgetController = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/TestWidgetController/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestWidgetController";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["RegisterValue"] = new ServiceVariable("RegisterValue");
		this.iVariables["RegisterIndex"] = new ServiceVariable("RegisterIndex");
		this.iVariables["UDN"] = new ServiceVariable("UDN");
}


ServiceTestWidgetController.prototype.ServiceName = function(){
	return this.iType;
}

ServiceTestWidgetController.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestWidgetController.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceTestWidgetController.prototype.CreateWidget = function(WidgetUdn, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CreateWidget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("WidgetUdn", WidgetUdn);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestWidgetController.prototype.RemoveWidget = function(WidgetUdn, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("RemoveWidget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("WidgetUdn", WidgetUdn);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestWidgetController.prototype.SetWidgetRegister = function(WidgetUdn, RegisterIndex, RegisterValue, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetWidgetRegister", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("WidgetUdn", WidgetUdn);
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
    


