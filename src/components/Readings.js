import React from 'react';
import ButtonMenu from './ButtonMenu';
import ReadingsElement from './ReadingsElement';

function Readings({ resetHandler, measureData }) {
  console.log(measureData);
  return (
    <>
      {measureData && <ButtonMenu resetHandler={resetHandler} />}
      {measureData &&
        Object.values(measureData).map((val, i) => (
          <ReadingsElement
            key={i}
            time={val.time}
            temperature={val.temperature}
            pressure={val.pressure}
            altitude={val.altitude}
          />
        ))}

      {!measureData && (
        <>
          <h1 className="text-2xl text-center">
            Waiting for sensor readings...
          </h1>
          <progress className="m-4 progress w-60"></progress>
        </>
      )}
    </>
  );
}
export default Readings;
