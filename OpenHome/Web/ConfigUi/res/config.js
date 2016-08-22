Config = function() {

    // FIXME - maybe not a good idea to update the dom from here
    // - however, should still have an intermediate UpdateCallback function here:
    // - UpdateCallback(aKey, aValue)
    // - so that webconfig.js doesn't have to parse them
    // - although, what about getting, e.g., lists of choices, among other things?
    // - must also be able to dynamically generate a table row based on ConfigVal type

    return {

        StartLongPolling: function(aStartedCallback, aUpdateCallback, aFailureCallback)
        {
            WebUi.StartLongPolling(aStartedCallback, aUpdateCallback, aFailureCallback);
        },

        EndLongPolling: function()
        {
            WebUi.EndLongPolling();
        },

        /**
         * Send data from browser to server.
         *
         * param aKey:              A key.
         * param aValue:            Value associated with aKey.
         * param aCallbackResponse: Response callback function of form CallbackResponse(aStringSent, aStringReceived).
         * param aCallbackError:    Error callback function of form CallbackError(aStringSent).
         * returns:                 null.
         */
        SendUpdateToServer: function(aKey, aValue, aCallbackResponse, aCallbackError)
        {
            var request = {};
            request.request = {};
            request.request.type = "update";
            request.request.key = aKey.toString();
            request.request.value = aValue.toString();  // All values handled as strings on server, irrespective of input type (i.e., num, choice or text).
            WebUi.SendUpdateToServer(JSON.stringify(request), aCallbackResponse, aCallbackError);
        },

        Reboot: function(aCallbackResponse, aCallbackError)
        {
            // Once the reboot request has been sent, there is no guarantee of
            // a response as the device may reboot immediately without sending
            // any response.
            // In that scenario, certainly don't want to suggest to client that
            // there has been an error, so ignore aCallbackError and provide a
            // custom error handler that redirects errors to aCallbackResponse.

            var CallbackError = function(aString, aResponseText, aResponseStatus) {
                aCallbackResponse(aString, "");
            }

            var request = {};
            request.request = {};
            request.request.type = "reboot";
            WebUi.SendUpdateToServer(JSON.stringify(request), aCallbackResponse, CallbackError);

            // Removing next vline fixes #4222 : "Reboot button on Konfig does not always reboot the device"
            //WebUi.RestartLongPolling();   // causing tabs to be destroyed before the reboot is executed.
        }
    };

}(); // Config
