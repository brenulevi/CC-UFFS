import { useEffect, useState } from "react";

import NavBar from "./components/NavBar";
import Card from "./components/Card";
import Table from "./components/Table";

import "./App.css";

import axios from "axios";

axios.defaults.baseURL = "http://localhost:3333/";
axios.defaults.headers.common["Content-Type"] =
  "application/json;charset=utf-8";

function App() {
  const [courseSelector, setCourseSelector] = useState(1);
  const [data, setData] = useState(undefined);
  const [courses, setCourses] = useState([]);

  useEffect(() => {
    const res = axios.get(`/schedule/${courseSelector}`);
    res.then((query) => {
      setData(query.data);
    });

  }, [courseSelector]);

  // On page load
  useEffect(() => {
    const res = axios.get("/course");
    res.then((query) => {
      setCourses(query.data);
    })
  }, [])

  return (
    <>
      <NavBar />

      <main>
        <section className="text-center">
          <h1>Cursos</h1>

          <div className="container">
            <div className="row row-cols-4">
              <Card courseName={(courses[0] !== undefined) ? courses[0].name : "Curso"} onSelectCourse={setCourseSelector} courses={courses} />
              <Card courseName={(courses[1] !== undefined) ? courses[1].name : "Curso"} onSelectCourse={setCourseSelector} courses={courses} />
              <Card courseName={(courses[2] !== undefined) ? courses[2].name : "Curso"} onSelectCourse={setCourseSelector} courses={courses} />
            </div>
          </div>
        </section>

        <div className="line-separator"></div>

        <section className="text-center">
          <h1>Visualizar Horários</h1>

          <div className="tables">
            <Table data={data} />
          </div>

        </section>
      </main>
    </>
  );
}

export default App;