JSB.newAddon = function(mainPath){
  JSB.require('SampleViewControllerW');
  var newAddonClass = JSB.defineClass('SampleWAddon : JSExtension', /*Instance members*/{
    //Window initialize
    sceneWillConnect: function() {
        self.layoutViewController = function(){
          var frame = Application.sharedInstance().studyController(self.window).view.bounds;
          var width = frame.width > 300?(300 + (frame.width - 300)/2):300;
          self.sampleController.view.frame = {x:(frame.width-width)/2,y:frame.height - 500,width:width,height:480};
        };
        self.sampleController = SampleViewControllerW.new();
        self.sampleController.mainPath = mainPath;
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
      NSTimer.scheduledTimerWithTimeInterval(0.2,false,function(){
        var sample_on = NSUserDefaults.standardUserDefaults().objectForKey('marginnote_sample_w_on');
        if(sample_on == true){// Not support in card deck mode
          Application.sharedInstance().studyController(self.window).view.addSubview(self.sampleController.view);
          self.layoutViewController();
          Application.sharedInstance().studyController(self.window).refreshAddonCommands();
        }
      });
    },
    notebookWillClose: function(notebookid) {
    },
    documentDidOpen: function(docmd5) {
    },
    documentWillClose: function(docmd5) {
    },
    controllerWillLayoutSubviews: function(controller) {
      //在这里添加窗口位置布局的代码
      if(controller == Application.sharedInstance().studyController(self.window)){
          self.layoutViewController();
      }
    },
    queryAddonCommandStatus: function() {
      return {image:'sample.png',object:self,selector:'toggleSample:',checked:(self.sampleController.view.window?true:false)};
    },
    toggleSample: function(sender) {
      if(self.sampleController.view.window){
        self.sampleController.view.removeFromSuperview();
        NSUserDefaults.standardUserDefaults().setObjectForKey(false,'marginnote_sample_w_on');
      }
      else{
        Application.sharedInstance().studyController(self.window).view.addSubview(self.sampleController.view);        
        self.layoutViewController();
        NSUserDefaults.standardUserDefaults().setObjectForKey(true,'marginnote_sample_w_on');
        NSTimer.scheduledTimerWithTimeInterval(0.2,false,function(){ 
          Application.sharedInstance().studyController(self.window).becomeFirstResponder(); //For dismiss keyboard on iOS
        });
      }
      Application.sharedInstance().studyController(self.window).refreshAddonCommands();
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

