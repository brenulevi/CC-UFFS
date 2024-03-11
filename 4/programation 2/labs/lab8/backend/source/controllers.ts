import { Request, Response } from "express";

export async function getCourse(req: Request, res: Response) {
  res.json({ message: "Hello World" });
}
