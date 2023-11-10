import React, { useEffect, useState } from "react";

import "./Navbar.css";

import logo from "../images/logo.png";

function Navbar({ setPage }) {
  const [activePage, setActivePage] = useState(0);

  useEffect(() => {
    const list = document.querySelector(".Navbar-menu ul").children;
    Array.from(list).forEach((element) => {
      element.classList.remove("active");
    });

    switch (activePage) {
      case 0:
        document.querySelector(".Navbar-menu ul li.l0").classList.add("active");
        break;
      case 1:
        document.querySelector(".Navbar-menu ul li.l1").classList.add("active");
        break;
      case 2:
        document.querySelector(".Navbar-menu ul li.l2").classList.add("active");
        break;
      case 3:
        document.querySelector(".Navbar-menu ul li.l3").classList.add("active");
        break;
      default:
        break;
    }

    setPage(activePage);
  }, [activePage, setPage]);

  return (
    <header id="Navbar-header">
      <nav className="Navbar-nav">
        <div className="Navbar-logo">
          <img src={logo} alt="Logo da UFFS" />
        </div>
        <div className="Navbar-menu">
          <ul>
            <li className="l0 active" onClick={() => setActivePage(0)}>
              <a href="#header">Adicionar curso</a>
            </li>
            <li className="l1" onClick={() => setActivePage(1)}>
              <a href="#header">Adicionar CCR</a>
            </li>
            <li className="l2" onClick={() => setActivePage(2)}>
              <a href="#header">Adicionar horário</a>
            </li>
            <li className="l3" onClick={() => setActivePage(3)}>
              <a href="#header">Visualizar curso</a>
            </li>
          </ul>
        </div>
      </nav>
    </header>
  );
}

export default Navbar;
