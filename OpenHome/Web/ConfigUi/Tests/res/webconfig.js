function StartLongPolling()
{
    var gConfigValNumLimits = [];
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
            limits = gConfigValNumLimits[i];
            if (limits.Key() == aKey) {
                if (aValue >= limits.Min() && aValue <= limits.Max()) {
                    SendUpdate(aKey, aValue);
                }
                else {
                    alert(aKey + " value of " + aValue + " is outwith range: " + limits.Min() + ".." + limits.Max());
                }
            }
        }
    }

    var ValidateTextInput = function(aKey, aValue)
    {
        for (var i=0; i<gConfigValTextLimits.length; i++) {
            limits = gConfigValTextLimits[i];
            if (limits.Key() == aKey) {
                if (aValue <= limits.MaxLength()) {
                    SendUpdate(aKey, aValue);
                }
                else {
                    alert(aKey + " value of " + aValue + " is longer than: " + limits.MaxLength() + " characters");
                }
            }
        }
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
            option.text = options[i];
            elemSelect.add(option);
        }
        elemSelect.onblur = function () {SendUpdate(elemSelect.id, elemSelect.value);}
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

    var CreateElement= function(aJsonConfigVal)
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
            var row = document.createElement("row");
            row.appendChild(colName);
            row.appendChild(colInput);

            container.appendChild(row);

            // return row;
            return document.getElementById(key);
        }
    }

    // FIXME - move this to config.js
    var UpdateCallback = function(aResponse)
    {
        if (aResponse != null && aResponse != "") {
            var key = aResponse.key;
            var val = aResponse.value;
            var elem = document.getElementById(key);
            if (elem != null) {
                elem.value = val;       // FIXME - is this valid for all element types in use?
            }
            else {
                // Element not found; may be one that has just been discovered.
                // Check if an element can be created and set the value. Ignore it
                // otherwise.
                elem = CreateElement(aResponse);
                if (elem != null) {
                    elem.value = val;   // FIXME - is this valid for all element types in use?
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