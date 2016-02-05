function StartLongPolling()
{
    var gConfigValNumLimits = [];
    var gConfigValChoiceOptions = [];
    var gConfigValTextLimits = [];

    var LongPollStarted = function()
    {
        // Do nothing.
    }

    var ConfigNumLimits = function(aKey, aMin, aMax)
    {
        this.iKey = aKey;
        this.iMin = aMin;
        this.iMax = aMax;
    }

    ConfigNumLimits.prototype.Key = function()
    {
        return this.iKey;
    }

    ConfigNumLimits.prototype.Min = function()
    {
        return this.iMin;
    }

    ConfigNumLimits.prototype.Max = function()
    {
        return this.iMax;
    }

    var ConfigChoiceOptions = function(aKey, aOptions)
    {
        this.iKey = aKey;
        this.iOptions = aOptions;
    }

    ConfigChoiceOptions.prototype.Key = function()
    {
        return this.iKey;
    }

    ConfigChoiceOptions.prototype.Options = function()
    {
        return this.iOptions;
    }

    var ConfigTextLimits = function(aKey, aMaxLength)
    {
        this.iKey = aKey;
        this.iMaxLength = aMaxLength;
    }

    ConfigTextLimits.prototype.Key = function()
    {
        return this.iKey;
    }

    ConfigTextLimits.prototype.MaxLength = function()
    {
        return this.iMaxLength;
    }

    var ValidateNumInput = function(aKey, aValue)
    {
        for (var i=0; i<gConfigValNumLimits.length; i++) {
            var limits = gConfigValNumLimits[i];
            if (limits.Key() == aKey) {
                if (aValue >= limits.Min() && aValue <= limits.Max()) {
                    SendUpdate(aKey, aValue);
                    return;
                }
                else {
                    alert(aKey + " value of " + aValue + " is outwith range: " + limits.Min() + ".." + limits.Max());
                    return;
                }
            }
        }
        alert("No such key: " + aKey);
    }

    var ValidateChoiceInput = function(aKey, aValue)
    {
        for (var i=0; i<gConfigValChoiceOptions.length; i++) {
            var key = gConfigValChoiceOptions[i].Key();
            var options = gConfigValChoiceOptions[i].Options();
            if (key == aKey) {
                for (var j=0; j<options.length; j++) {
                    if (options[j].value == aValue) {
                        SendUpdate(aKey, options[j].id.toString());
                        return;
                    }
                }
                alert(aKey + " value of " + aValue + " not found");
                return;
            }
        }
        alert("No such key: " + aKey);
    }

    var ValidateTextInput = function(aKey, aValue)
    {
        for (var i=0; i<gConfigValTextLimits.length; i++) {
            var limits = gConfigValTextLimits[i];
            if (limits.Key() == aKey) {
                if (aValue.length <= limits.MaxLength()) {
                    SendUpdate(aKey, aValue);
                    return;
                }
                else {
                    alert(aKey + " value of " + aValue + " is longer than: " + limits.MaxLength() + " characters");
                    return;
                }
            }
        }
        alert("No such key: " + aKey);
    }

    var CreateReadOnlyElement = function(aJsonConfigReadOnlyVal)
    {
        var elemInput = document.createElement("input");
        elemInput.type = "text";
        elemInput.id = aJsonConfigReadOnlyVal.key;
        elemInput.name = aJsonConfigReadOnlyVal.key;
        elemInput.readOnly = true;
        return elemInput;
    }

    var CreateReadOnlyListElement = function(aJsonConfigReadOnlyListVal)
    {
        var elemInput = document.createElement("input");
        elemInput.type = "text";
        elemInput.id = aJsonConfigReadOnlyListVal.key;
        elemInput.name = aJsonConfigReadOnlyListVal.key;
        elemInput.readOnly = true;
        return elemInput;
    }

    var CreateNumElement = function(aJsonConfigNumVal)
    {
        var elemInput = document.createElement("input");
        elemInput.type = "text";
        elemInput.id = aJsonConfigNumVal.key;
        elemInput.name = aJsonConfigNumVal.key;
        gConfigValNumLimits.push(new ConfigNumLimits(aJsonConfigNumVal.key, aJsonConfigNumVal.meta.min, aJsonConfigNumVal.meta.max));
        elemInput.onblur = function () {ValidateNumInput(elemInput.id, elemInput.value);}
        return elemInput;
    }

    var CreateChoiceElement = function(aJsonConfigChoiceVal)
    {
        var options = aJsonConfigChoiceVal.meta.options;
        var elemSelect = document.createElement("select");
        elemSelect.id = aJsonConfigChoiceVal.key;
        elemSelect.name = aJsonConfigChoiceVal.key;
        elemSelect.multiple = false;
        for (var i=0; i<options.length; i++) {
            var option = document.createElement("option");
            option.text = options[i].value;
            option.value = option.text;
            elemSelect.add(option);
        }
        gConfigValChoiceOptions.push(new ConfigChoiceOptions(aJsonConfigChoiceVal.key, aJsonConfigChoiceVal.meta.options));
        elemSelect.onblur = function () {ValidateChoiceInput(elemSelect.id, elemSelect.value);}
        return elemSelect;
    }

    var CreateTextElement = function(aJsonConfigTextVal)
    {
        var elemInput = document.createElement("input");
        elemInput.type = "text";
        elemInput.id = aJsonConfigTextVal.key;
        elemInput.name = aJsonConfigTextVal.key;
        gConfigValTextLimits.push(new ConfigTextLimits(aJsonConfigTextVal.key, aJsonConfigTextVal.meta.maxlength));
        elemInput.onblur = function () {ValidateTextInput(elemInput.id, elemInput.value);}
        return elemInput;
    }

    var CreateValElement = function(aJsonConfigVal)
    {
        if (aJsonConfigVal.type == "read-only") {
            return CreateReadOnlyElement(aJsonConfigVal)
        }
        if (aJsonConfigVal.type == "read-only-list") {
            return CreateReadOnlyListElement(aJsonConfigVal)
        }
        if (aJsonConfigVal.type == "numeric") {
            return CreateNumElement(aJsonConfigVal)
        }
        else if (aJsonConfigVal.type == "choice") {
            return CreateChoiceElement(aJsonConfigVal)
        }
        else if (aJsonConfigVal.type == "text") {
            return CreateTextElement(aJsonConfigVal)
        }
        else {
            // Bad ConfigVal type.
        }
    }

    var CreateElement = function(aJsonConfigVal)
    {
        var elem = document.getElementById(aJsonConfigVal.key);
        if (elem != null) {
            return elem;
        }

        var containerId = "ConfigValContainer"
        var container = document.getElementById(containerId);
        if (container == null) {
            alert("Error: Config.StartLongPolling.CreateElement() No element with id \""+containerId+"\"");
            return null;
        }
        else {
            var key = aJsonConfigVal.key;

            // Create a name column.
            var colName = document.createElement("td");
            var nameText = document.createTextNode(key);
            colName.appendChild(nameText);

            // Create an input column.
            var colInput = document.createElement("td");
            var elemVal = CreateValElement(aJsonConfigVal); // value is not set; set outwith this function
            colInput.appendChild(elemVal);

            // Create a row to hold the columns of data.
            var row = document.createElement("tr");
            row.appendChild(colName);
            row.appendChild(colInput);

            container.appendChild(row);

            // return row;
            return document.getElementById(key);
        }
    }

    var SetElementValue = function(aElement, aJsonResponse)
    {
        // Element should NOT be null.
        if (aJsonResponse.type == "read-only") {
            aElement.value = aJsonResponse.value;
        }
        if (aJsonResponse.type == "read-only-list") {
            aElement.value = aJsonResponse.value;
        }
        if (aJsonResponse.type == "numeric") {
            aElement.value = aJsonResponse.value;
        }
        else if (aJsonResponse.type == "choice") {
            var id = aJsonResponse.value;
            var options = aJsonResponse.meta.options;
            for (var i=0; i<options.length; i++) {
                if (id == options[i].id) {
                    aElement.value = options[i].value;
                }
            }
        }
        else if (aJsonResponse.type == "text") {
            aElement.value = aJsonResponse.value;
        }
    }

    // FIXME - move this to config.js
    var UpdateCallback = function(aResponse)
    {
        if (aResponse != null && aResponse != "") {
            var key = aResponse.key;
            //var val = aResponse.value;
            var elem = document.getElementById(key);
            if (elem != null) {
                SetElementValue(elem, aResponse);
            }
            else {
                // Element not found; may be one that has just been discovered.
                // Check if an element can be created and set the value. Ignore it
                // otherwise.
                elem = CreateElement(aResponse);
                if (elem != null) {
                    SetElementValue(elem, aResponse);
                }
            }
        }
    }

    // FIXME - move this to WebUi? - maybe not
    function DummyCallbackFailure()
    {
        // This, combined with the reconnect behaviour, causes long-polling to
        // be restarted again after the connection has just been re-established.
        var content = "<h1>Error: HTTP Framework cannot connect to server</h1>";
        document.body.innerHTML = content;
    }

    Config.StartLongPolling(LongPollStarted, UpdateCallback, DummyCallbackFailure);
}

function EndLongPolling()
{
    Config.EndLongPolling();
}

function SendUpdate(aKey, aValue)
{

    var DummyUpdateCallbackResponse = function(aStringSent, aStringReceived)
    {
        //alert("DummyUpdateCallbackResponse sent: "+aStringSent+", rcvd: "+aStringReceived);
    }

    var DummyUpdateCallbackError = function(aStringSent)
    {
        //alert("DummyUpdateCallbackError: "+aStringSent);
    }

    Config.SendUpdateToServer(aKey, aValue, DummyUpdateCallbackResponse, DummyUpdateCallbackError);
}

function Reboot()
{
    var DummyUpdateCallbackResponse = function(aStringSent, aStringReceived)
    {
        //alert("DummyUpdateCallbackResponse sent: "+aStringSent+", rcvd: "+aStringReceived);
    }

    var DummyUpdateCallbackError = function(aStringSent)
    {
        //alert("DummyUpdateCallbackError: "+aStringSent);
    }

    Config.Reboot(DummyUpdateCallbackResponse, DummyUpdateCallbackError);
}
