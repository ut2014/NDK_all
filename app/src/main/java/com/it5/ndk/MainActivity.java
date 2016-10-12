package com.it5.ndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    DataProvider dataProvider;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dataProvider=new DataProvider();
        ((TextView)findViewById(R.id.text)).setText(dataProvider.stringFromJNI());
    }

    public void onClick(View view){
        int id=view.getId();
        switch (id) {
            case R.id.add:
                int result=dataProvider.add(1,2);
                Toast.makeText(getApplicationContext(),"the add result: "+result,Toast.LENGTH_SHORT).show();
                break;
            case R.id.sayHelloInc:
                dataProvider.sayHelloInc("dsa");
                break;
            case R.id.intMethod:
                int[] array={1,2,3,4,5};
                dataProvider.intMethod(array);
                break;
            default:
                break;
        }
    }
}
