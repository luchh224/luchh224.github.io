package com.zybooks.weightlosskcl;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class AddActivity extends AppCompatActivity {

    //This is going to create variables to edit text
    private EditText dateEdt, weightEdt;
    private Button switchToMainActivity;
    private DBHandlerWeight dbHandlerWeight;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_screen);

        //This is going to initialize our variables. Our edit text views are already assigned names
        //and I will use those on the findViewByID method
        dateEdt = findViewById(R.id.editTextDate);
        weightEdt = findViewById(R.id.editweight);

        //this will create a DBHandlerWeight class and the context will be passed to it
        dbHandlerWeight = new DBHandlerWeight(AddActivity.this);

        switchToMainActivity = findViewById(R.id.submit_button);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String date = dateEdt.getText().toString();
                String weight = weightEdt.getText().toString();

                //This is going to be the if statement to check if the fields have all been filled in before proceeding to prevent a null entry
                //from happening where nothing is filled in
                if (date.isEmpty() && weight.isEmpty()) {
                    Toast.makeText(AddActivity.this, "Please fill in all of the fields", Toast.LENGTH_SHORT).show();
                    return;
                }

                //this will add the new weight and date and pass the values to the sqlite data
                dbHandlerWeight.addNewWeight(weight, date);
                dateEdt.setText("");
                weightEdt.setText("");

                startActivity(new Intent(AddActivity.this, MainActivity.class));
                Toast.makeText(AddActivity.this, "New Entry Submitted Successfully!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}
