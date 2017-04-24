using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
 
namespace Mostek
{
class Program
{
enum Tlok
{
cd,
dvd,
bd
}
 
 
interface PlytkaInterface {
void akcja();
}
 
 
abstract class Plytka
{
protected PlytkaInterface plytkaInterface;
protected Tlok type;
protected String name;
 
 
public Plytka(Tlok type, String name, PlytkaInterface plytkaImp)
{
this.type = type;
this.name = name;
this.plytkaInterface = plytkaImp;
}
 
 
public String Get()
{
return name + " " + type;
}
 
 
public void Set(String s, Tlok type)
{
this.name = s;
this.type = type;
}
 
 
public abstract void akcja();
}
 
 
class KPlytka : Plytka {
public KPlytka(Tlok type, String name, PlytkaInterface plytkaInterface) : base(type,name,plytkaInterface)
{
}
 
public override void akcja()
{
plytkaInterface.akcja();
}
 
}
 
 
class Nagrywanie : PlytkaInterface {
public void akcja()
{
Console.WriteLine("Nagrywam plytke");
}
}
 
 
class Odczytywanie : PlytkaInterface {
public void akcja()
{
Console.WriteLine("Odczytuje plytke");
}
}
 
 
 
static void Main(string[] args)
{
Plytka ob1 = new KPlytka(Tlok.dvd, "TDK", new Nagrywanie());
Plytka ob2 = new KPlytka(Tlok.cd, "Dysan", new Odczytywanie());
ob1.akcja();
Console.WriteLine(ob1.Get() + "\n");
ob2.akcja();
Console.WriteLine(ob2.Get() + "\n");
ob1.Set("Verbatim", Tlok.bd);
ob1.akcja();
Console.WriteLine(ob1.Get() + "\n");
Console.ReadKey(true);
}
}
}