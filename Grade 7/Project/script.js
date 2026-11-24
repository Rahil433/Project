$(document).ready(function () {
  var accessKey = "cnUtajlBUUhPcmpWSU5jMVEwM0o=";
  var secretKey = "SzdTRXNvcWJlTW5HS1lWSTZmdU9uSTV3SFBUX29HY05ldw==";
  var deviceId = "sc00802";

  function startSensor() {
    var settings = {
      "url": "https://wizklub.com/api/secured/wiziot-poll-request/",
      "method": "POST",
      "dataType": "json",
      "contentType": "application/json; charset=utf-8",
      "headers": { "Api-Access-Key": accessKey, "Api-Secret-Key": secretKey, "Content-Type": "application/json" },
      "data": JSON.stringify({ "mode": "WRITE", "device_id": deviceId, "source": "API", "api": "sensor", "sensor": "weather", "state": "start" }),
    };

    $.ajax(settings).done(function (response) {
      console.log(response);
      fetchTemp();
    });
  }

  function fetchTemp() {
    var settings = {
      "url": "https://wizklub.com/api/secured/wiziot-poll-request/",
      "method": "POST",
      "dataType": "json",
      "contentType": "application/json; charset=utf-8",
      "headers": { "Api-Access-Key": accessKey, "Api-Secret-Key": secretKey, "Content-Type": "application/json" },
      "data": JSON.stringify({ "mode": "READ", "device_id": deviceId, "source": "API", "api": "sensor", "sensor": "weather" }),
    };

    $.ajax(settings).done(function (response) {
      console.log(response);
      let temp = response.response.worker_response.iot.value.temperature;
      let tempstring = "Temp :" + temp + "C";
      console.log(tempstring);
      dispTemp(tempstring);
      $('#result').text(temp);
    });
  }

  function dispTemp(temp) {
    var settings = {
      "url": "https://wizklub.com/api/secured/wiziot-poll-request/",
      "method": "POST",
      "dataType": "json",
      "contentType": "application/json; charset=utf-8",
      "headers": { "Api-Access-Key": accessKey, "Api-Secret-Key": secretKey, "Content-Type": "application/json" },
      "data": JSON.stringify({ "mode": "WRITE", "device_id": deviceId, "source": "API", "api": "oled", "type": "text", "msg_to_write": temp, "x_axis": "2", "y_axis": "3" }),
    };
    $.ajax(settings).done(function (response) {
      console.log(response);
    })
  }

  $('#output').click(function () {
    startSensor();
  })

})
