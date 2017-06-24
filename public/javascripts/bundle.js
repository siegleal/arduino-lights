$(function() {
  var $ipInput = $('.ip');
  var $colorInput = $('.colorpicker').colorpicker();

  $('.color-form').submit(function(e) {
    e.preventDefault();
    var ip = $ipInput.val();
    var color = $colorInput.colorpicker('getValue');
    if(!ip.length) {
      console.log('ip must not be blank')
      return false;
    }
    if(color.length !== 7 && !color.startsWith('#')) {
      console.log('color must be a hex value');
      return false;
    }
    $.ajax({
      type: "POST",
      url: '/setcolor',
      data: {
        ip: ip,
        color: color
      }
    }).done(function(data) {
      console.log(data);
    }).fail(function(err) {
      console.log(err);
    });
  });
});