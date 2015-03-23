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
            WebUi.SendUpdateToServer(aKey+" "+aValue, aCallbackResponse, aCallbackError);
        }
    };

}(); // Config
