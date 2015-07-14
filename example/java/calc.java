/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package calc;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

/**
 * @author Administrator
 */
import javax.microedition.lcdui.Canvas;

public class calc extends MIDlet {

    private screen scr;

    public void startApp() {
        scr = new screen();
        Display.getDisplay(this).setCurrent(scr);
    }

    public void pauseApp() {
    }

    public void destroyApp(boolean unconditional) {
    }
}

class screen extends Canvas {

    private int first;
    private int type;
    private int second;

    protected void paint(Graphics g) {
        g.setColor(255, 255, 255);
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(0, 0, 0);
        String tmp;
        if(second == 0)
            tmp = Integer.toString(first);
        else
            tmp = Integer.toString(second);
        g.drawString(tmp, getWidth() - 3, 30, Graphics.TOP | Graphics.RIGHT);
    }

    public void screen() {
        first = 0;
        second = 0;
        type = 0;
    }

    private void c() {
        switch (type) {
            case 0:
                first += second;
                break;
            case 1:
                first -= second;
                break;
            case 2:
                first *= second;
                break;
            case 3:
                first /= second;
                break;
        }
        second = 0;
    }

    public void keyPressed(int keyCode) {
        if (keyCode >= KEY_NUM0 && keyCode <= KEY_NUM9) {
            second = second * 10 + keyCode - KEY_NUM0;
        }
        if (keyCode == -1) {
            c();
            type = 0;
        }
        if (keyCode == -2) {
            c();
            type = 1;
        }
        if (keyCode == -3) {
            c();
            type = 2;
        }
        if (keyCode == -4) {
            c();
            type = 3;
        }
        if (keyCode == -5) {
            c();
        }
        repaint();
    }
}
