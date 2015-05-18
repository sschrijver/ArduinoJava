package test;

public class Aansturing {
    private Connectie c;
    
    public Aansturing(Connectie c)
    {
        this.c = c;
    } 
           
    
    public void naarLinks()
    {
        c.sendData("naarLinks");
        try
        {
            Thread.sleep(2000);
        }
        catch (InterruptedException ie)
        {
        }
    }
    
    public void naarRechts()
    {
        c.sendData("naarRechts");
        try
        {
            Thread.sleep(2000);
        }
        catch (InterruptedException ie)
        {
        }
    }

}
