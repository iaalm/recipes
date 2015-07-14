var cecosvt = {  
  smartMouseWheel: function () {
    var productAreaHeight = $(window).height() - 55;
    $(".product-area").css({'height': productAreaHeight});
    var sectionsAry = ['body','#top','#ecology','#culture','#organic','#healthy'];
    var totalSection = sectionsAry.length;
    var currentSectionId = 1; //origin is -1
    var isSectionMovementBusy = false;
    var counter = 0;
    $('html,body').on('mousewheel', function(event, delta) {
      
      if(isSectionMovementBusy == true) return false;
      event.preventDefault();

      if(delta > 0){
        currentSectionId--;   
      }else{
        currentSectionId++;
      }
      if(currentSectionId < 0) {
        currentSectionId = 0;
        return false;
      }
      if(currentSectionId > totalSection-1) {
        currentSectionId = totalSection-1;
        return false;
      } 
      var yPos = $(sectionsAry[currentSectionId]).offset().top -55;
      if(currentSectionId == 1) yPos -=50;
      
      isSectionMovementBusy = true;  //easeInOutExpo easeInOutCubic easeInOutQuart
      $("#sider-nav a").each(function(){
          if($(this).attr("href")==sectionsAry[currentSectionId]){
              $(this)
                .addClass("active")
                .parent().siblings().children('a').removeClass("active"); 
          }
      });

      $('body,html').stop(true, false).animate({'scrollTop':yPos+'px'},1000, 'easeInOutExpo',function(){
        isSectionMovementBusy = false;
      })
      return false; 
    });
  },
  siderNav: function(){
    $("#sider-nav a").click(function(e){
        var href = $(this).attr("href");
        var pos = $(href).offset().top - 55;
        console.log($(this).siblings());
        $(this)
          .addClass("active")
          .parent().siblings().children('a').removeClass("active");  
        $("html,body").animate({scrollTop: pos}, 1000, 'easeInOutExpo',function(){
        });

        return false;
    });
  },
  responseMenu: function () {
    $("div#showMenu").on("click", function(){
      $(".menu").toggle(200);
    });
  },
  init: function () {
    this.smartMouseWheel();
    this.responseMenu();
    this.siderNav();
  }
};

$(function(){
  cecosvt.init();
});
