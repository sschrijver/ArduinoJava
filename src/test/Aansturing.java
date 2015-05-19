package test;

public class Aansturing
{
    private Connectie c;

    public Aansturing(Connectie c)
    {
        this.c = c;
    }

    public void stuur(String s)
    {
        c.sendData(s);
        try
        {
            while(!c.isOntvangen())
            {
                Thread.sleep(1);
            }
        }
        catch (InterruptedException ie)
        {
        }
    }

}
