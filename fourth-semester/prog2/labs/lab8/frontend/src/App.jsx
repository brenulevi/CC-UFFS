import React, { useState } from "react";

import Navbar from "./components/Navbar";
import AddCourse from "./components/AddCourse";
import AddCcr from "./components/AddCcr";
import AddSchedule from "./components/AddSchedule";
import VisualizeCourse from "./components/VisualizeCourse";

function App() {
  const [activePage, setActivePage] = useState(0);

  return (
    <>
        <Navbar setPage={setActivePage} />
        {activePage === 0 ? <AddCourse /> : activePage === 1 ? <AddCcr /> : activePage === 2 ? <AddSchedule /> : <VisualizeCourse />}
    </>
    );
}

export default App;
