$(document).ready(function(){
	$(".float-window").mouseover(function(event){
		$(event.currentTarget).children(".float-text").css("display","block");
	})
	$(".float-window").mouseout(function(){
		$(event.currentTarget).children(".float-text").css("display","none");
	})
});