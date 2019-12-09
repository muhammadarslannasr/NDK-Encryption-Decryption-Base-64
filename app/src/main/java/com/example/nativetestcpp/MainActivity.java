package com.example.nativetestcpp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    TextView tv;
    Button btnJNI,btnencode,btndecode;

    String abc = "hello sikander";
    String bcd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        btnJNI = findViewById(R.id.btnJni);
     //   btnJNIStringArray = findViewById(R.id.btnJniStringArray);
        btnJNI.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String result = sendYourName("Anupam", "Chugh");
                tv.setText(result);
              //  Toast.makeText(getApplicationContext(), "Result from JNI is " + result, Toast.LENGTH_LONG).show();
            }
        });        btnencode = findViewById(R.id.btnencode);
     //   btnJNIStringArray = findViewById(R.id.btnJniStringArray);
        btnencode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String result = base64Encode(abc);
                tv.setText(result);
                bcd = result;
                Toast.makeText(getApplicationContext(), "Result from JNI is " + result, Toast.LENGTH_LONG).show();
            }
        });        btndecode = findViewById(R.id.btndecode);
     //   btnJNIStringArray = findViewById(R.id.btnJniStringArray);
        btndecode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String result = base64Decode(bcd);
                tv.setText(stringFromJNI());
                Toast.makeText(getApplicationContext(), "Result from JNI is " + result, Toast.LENGTH_LONG).show();
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String sendYourName(String firstName, String lastName);
    public native String base64Encode(String data);
    public native String base64Decode(String data);
}
