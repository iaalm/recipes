/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package draw;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

/**
 * @author Administrator
 */
public class Midlet extends MIDlet {

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

    private int prex, prey, x, y;
    private final int len = 100;
    private line[] tab = new line[len];

    public screen() {
        prex = -1;
        prey = -1;
        x = getWidth() / 2;
        y = getHeight() / 2;
        int i;
        for(i = 0;i < len;i++)
            tab[i] = new line();
    }

    protected void paint(Graphics g) {
        g.setColor(255, 255, 255);
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(255, 0, 0);
        if(prex != -1)
            g.drawLine(prex, prey, x, y);
        g.drawRect(x - 1, y - 1, 3, 3);
        int i;
        for (i = 0; i < len; i++) {
            tab[i].draw(g);
        }
    }

    public void keyPressed(int keyCode) {
        if (keyCode == -1) {
            y -= 10;
        }
        if (keyCode == -2) {
            y += 10;
        }
        if (keyCode == -3) {
            x -= 10;
        }
        if (keyCode == -4) {
            x += 10;
        }
        if (keyCode == -5) {
            if (prex == -1) {
                prex = x;
                prey = y;
            } else {
                int i;
                for (i = 0; i < len; i++) {
                    if (!tab[i].enable) {
                        tab[i].set(prex, prey, x, y);
                        prex = -1;
                        break;
                    }
                }
            }
        }
        repaint();
    }
}

class line {

    private int x0, y0, x1, y1;
    public boolean enable;

    public line() {
        enable = false;
    }

    public line(int t1, int t2, int t3, int t4) {
        x0 = t1;
        y0 = t2;
        x1 = t3;
        y1 = t4;
        enable = true;
    }

    public void set(int t1, int t2, int t3, int t4) {
        x0 = t1;
        y0 = t2;
        x1 = t3;
        y1 = t4;
        enable = true;
    }

    public void disable() {
        enable = false;
    }

    public void draw(Graphics g) {
        if (enable) {
            g.setColor(255, 0, 0);
            g.drawLine(x0, y0, x1, y1);
        }
    }
}
