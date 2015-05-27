package test;

public class main
{
    public static void main(String[] args) throws Exception
    {
        Connectie connectie = new Connectie();
        Aansturing aansturing = new Aansturing(connectie);
        if (connectie.initialize())
        {
            aansturing.stuur("1,0");
            
            aansturing.stuur("3,-3");
            aansturing.stuur("1,-1");
            aansturing.stuur("0,4");
            
            
            aansturing.stuur("-4,0");
            
            aansturing.stuur("drop");
            connectie.close();
        }

    }

}
