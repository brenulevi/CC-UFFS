import React from "react";

import TableBootstrap from "react-bootstrap/Table";

function Table({ data }) {
    return (
        <>
            <TableBootstrap striped bordered hover size="lg">
                <thead>
                    <tr>
                        <th>#</th>
                        <th>Segunda</th>
                        <th>Terça</th>
                        <th>Quarta</th>
                        <th>Quinta</th>
                        <th>Sexta</th>
                    </tr>
                </thead>
                <tbody>

                    <tr className="1">
                        <th>Manhã</th>
                        <td>{(data !== undefined) ? data.schedule.monday.morning : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.tuesday.morning : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.wednesday.morning : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.thursday.morning : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.friday.morning : ""}</td>
                    </tr>
                    <tr className="2">
                        <th>Tarde</th>
                        <td>{(data !== undefined) ? data.schedule.monday.afternoon : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.tuesday.afternoon : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.wednesday.afternoon : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.thursday.afternoon : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.friday.afternoon : ""}</td>
                    </tr>
                    <tr className="3">
                        <th>Noite</th>
                        <td>{(data !== undefined) ? data.schedule.monday.night : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.tuesday.night : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.wednesday.night : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.thursday.night : ""}</td>
                        <td>{(data !== undefined) ? data.schedule.friday.night : ""}</td>
                    </tr>
                </tbody>
            </TableBootstrap>
        </>
    );
}

export default Table;