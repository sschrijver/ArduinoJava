package test;

public class main
{
    public static void main(String[] args) throws Exception
    {
        Connectie connectie = new Connectie();
        Aansturing aansturing = new Aansturing(connectie);
        if (connectie.initialize())
        {
            aansturing.naarLinks();
            aansturing.naarRechts();
            connectie.close();
        }

        // Wait 5 seconds then shutdown
        try
        {
            Thread.sleep(2000);
        }
        catch (InterruptedException ie)
        {
        }
    }

}
