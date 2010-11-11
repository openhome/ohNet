 

/**
 * Proxy for zapp.org:TestWidget:1
 */

var ServiceTestWidget = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/zapp.org-TestWidget-1/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestWidget";
	this.iVersion = "1";
	this.iServiceName = "zapp.org-TestWidget-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
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


ServiceTestWidget.prototype.RegisterValue_Changed = function (aStateChangedFunction) {
    this.Variables().RegisterValue.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.RegisterIndex_Changed = function (aStateChangedFunction) {
    this.Variables().RegisterIndex.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadWriteRegister0_Changed = function (aStateChangedFunction) {
    this.Variables().ReadWriteRegister0.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadWriteRegister1_Changed = function (aStateChangedFunction) {
    this.Variables().ReadWriteRegister1.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadWriteRegister2_Changed = function (aStateChangedFunction) {
    this.Variables().ReadWriteRegister2.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadWriteRegister3_Changed = function (aStateChangedFunction) {
    this.Variables().ReadWriteRegister3.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadOnlyRegister4_Changed = function (aStateChangedFunction) {
    this.Variables().ReadOnlyRegister4.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadOnlyRegister5_Changed = function (aStateChangedFunction) {
    this.Variables().ReadOnlyRegister5.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadOnlyRegister6_Changed = function (aStateChangedFunction) {
    this.Variables().ReadOnlyRegister6.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestWidget.prototype.ReadOnlyRegister7_Changed = function (aStateChangedFunction) {
    this.Variables().ReadOnlyRegister7.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceTestWidget.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceTestWidget.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestWidget.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceTestWidget.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceTestWidget.prototype.Udn = function () {
    return this.iUdn;
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

ServiceTestWidget.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceTestWidget.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
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



