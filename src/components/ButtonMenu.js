import React from 'react';
import Modal from './Modal';

function ButtonMenu({ resetHandler }) {
  return (
    <>
      <div className="mb-2">
        <label className="btn" htmlFor="main-modal">
          RESET MEASUREMENTS
        </label>
        <Modal resetHandler={resetHandler} />
      </div>
    </>
  );
}

export default ButtonMenu;
