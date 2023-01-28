import React from 'react';
import { BiTime } from 'react-icons/bi';
import { TbTemperature } from 'react-icons/tb';
import { IconContext } from 'react-icons';
import { FaMountain } from 'react-icons/fa';
import { AiOutlineDownload } from 'react-icons/ai';

function ReadingsElement({ temperature, altitude, pressure, time }) {
  return (
    <IconContext.Provider value={{ color: 'black', size: '2em' }}>
      <div className="stats stats-vertical lg:stats-horizontal shadow m-6 hover:bg-slate-50">
        <div className="stat">
          <div className="stat-title">Time</div>
          <div className="stat-value font-medium">{time}</div>
          <div className="stat-figure text-secondary pt-7">
            <BiTime />
          </div>
        </div>

        <div className="stat">
          <div className="stat-figure text-secondary pt-7">
            <TbTemperature />
          </div>
          <div className="stat-title">Temperature</div>
          <div className="stat-value font-medium">{temperature}°C</div>
        </div>

        <div className="stat">
          <div className="stat-figure text-secondary pt-7">
            <FaMountain />
          </div>
          <div className="stat-title">Altitude</div>
          <div className="stat-value font-medium">{altitude}m</div>
        </div>

        <div className="stat">
          <div className="stat-figure text-secondary pt-7">
            <AiOutlineDownload />
          </div>
          <div className="stat-title">Pressure</div>
          <div className="stat-value font-medium">{pressure}hPa</div>
        </div>
      </div>
    </IconContext.Provider>
  );
}

export default ReadingsElement;
