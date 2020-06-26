JSB.newAddon = function(mainPath){
  var newAddonClass = JSB.defineClass('SampleHelloWorld : JSExtension', /*Instance members*/{
    //Window initialize
    sceneWillConnect: function() {
      Application.sharedInstance().showHUD('Hello World',self.window,2);
    },
    //Window disconnect
    sceneDidDisconnect: function() {
    },
    //Window resign active
    sceneWillResignActive: function() {
    },
    //Window become active
    sceneDidBecomeActive: function() {
    },
    notebookWillOpen: function(notebookid) {
      JSB.log('MNLOG Open Notebook: %@',notebookid);
    },
    notebookWillClose: function(notebookid) {
      JSB.log('MNLOG Close Notebook: %@',notebookid);
    },
    documentDidOpen: function(docmd5) {
    },
    documentWillClose: function(docmd5) {
    },
  }, /*Class members*/{
    addonDidConnect: function() {
    },
    addonWillDisconnect: function() {
    },
    applicationWillEnterForeground: function() {
    },
    applicationDidEnterBackground: function() {
    },
    applicationDidReceiveLocalNotification: function(notify) {
    },
  });
  return newAddonClass;
};

