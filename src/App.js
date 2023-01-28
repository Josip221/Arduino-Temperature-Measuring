import { initializeApp } from 'firebase/app';
import { useState, useEffect } from 'react';
import { getDatabase, onValue, ref, set } from 'firebase/database';
import Info from './components/Info';

import Readings from './components/Readings';

function App() {
  const firebaseConfig = {
    apiKey: `${process.env.REACT_APP_API_KEY}`,
    authDomain: `${process.env.REACT_APP_AUTH_DOMAIN}`,
    databaseURL: `${process.env.REACT_APP_DATABASE_URL}`,
    projectId: `${process.env.REACT_APP_PROJECT_ID}`,
    storageBucket: `${process.env.REACT_APP_STORAGE_BUCKET}`,
    messagingSenderId: `${process.env.REACT_APP_SENDER_ID}`,
    appId: `${process.env.REACT_APP_APP_ID}`,
  };

  const app = initializeApp(firebaseConfig);
  const db = getDatabase(app);

  const resetHandler = () => {
    set(ref(db, 'measure'), null);
  };
  const [measureData, setMeasureData] = useState(null);

  useEffect(() => {
    const measureDataRef = ref(db, 'measure');
    onValue(measureDataRef, snapshot => {
      setMeasureData(snapshot.val());
    });
  }, [db]);
  return (
    <div className="flex flex-col items-center font-quicksand">
      <Info />
      <Readings measureData={measureData} resetHandler={resetHandler} />
    </div>
  );
}

export default App;
