import React from 'react';

function Info() {
  return (
    <div className="mb-2">
      <h1 className="text-center  text-3xl sm:text-6xl font-black font-poppin rounded-lg m-8">
        TemperatureIO
      </h1>
      {/* <div>
        <p className="text-center">Wemos D1R2 board</p>
        <p className="text-center">ESP8266 WiFi communication</p>
        <p className="text-center">BMP280 sensor</p>
      </div> */}
      <div className="divider w-80 sm:w-full"></div>
    </div>
  );
}

export default Info;
