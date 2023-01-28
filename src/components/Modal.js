import React from 'react';

function Modal({ resetHandler }) {
  return (
    <>
      <input type="checkbox" id="main-modal" className="modal-toggle" />
      <div className="modal modal-bottom lg:modal-middle">
        <div className="modal-box">
          <h3 className="font-bold text-lg">Warning!</h3>
          <p className="py-4">
            This will delete all measurements collected in the database! Do you
            wish to proceed?
          </p>
          <div className="modal-action">
            <label htmlFor="main-modal" className="btn" onClick={resetHandler}>
              Yes
            </label>
            <label htmlFor="main-modal" className="btn">
              No
            </label>
          </div>
        </div>
      </div>
    </>
  );
}

export default Modal;
