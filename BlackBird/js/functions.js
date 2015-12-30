

$(window).scroll(function(){
  var wScroll = $(this).scrollTop();

  $('.logo').css({
    'transform' : 'translate(0px, '+ wScroll /2 +'%)'
  });

if(wScroll > $('.bubble-wrapper').offset().top - $(window).height()){

    $('.bubble-wrapper').css({'background-position':'center '+ (wScroll - $('.bubble-wrapper').offset().top) +'px'});
    var opacity = (wScroll - $('.bubble-wrapper').offset().top + 400) / (wScroll / 5);

    $('.window-tint').css({'opacity': opacity});}
});
