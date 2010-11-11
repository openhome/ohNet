 

/**
 * Proxy for zapp.org:TestWidgetController:1
 */

var ServiceTestWidgetController = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/zapp.org-TestWidgetController-1/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestWidgetController";
	this.iVersion = "1";
	this.iServiceName = "zapp.org-TestWidgetController-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["RegisterValue"] = new ServiceVariable("RegisterValue");
		this.iVariables["RegisterIndex"] = new ServiceVariable("RegisterIndex");
		this.iVariables["UDN"] = new ServiceVariable("UDN");
}


ServiceTestWidgetController.prototype.RegisterValue_Changed = function (aStateChangedFunction) {
    this.Variables().RegisterValue.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidgetController.prototype.RegisterIndex_Changed = function (aStateChangedFunction) {
    this.Variables().RegisterIndex.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidgetController.prototype.UDN_Changed = function (aStateChangedFunction) {
    this.Variables().UDN.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceTestWidgetController.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceTestWidgetController.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestWidgetController.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceTestWidgetController.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceTestWidgetController.prototype.Udn = function () {
    return this.iUdn;
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

ServiceTestWidgetController.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceTestWidgetController.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
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



