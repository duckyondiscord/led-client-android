package org.ducky.ledclient

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import org.ducky.ledclient.databinding.ActivityMainBinding
import android.util.Log
import android.widget.Button

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)


        // Example of a call to a native method
        binding.connectbutton.setOnClickListener {
            val result = stringFromJNI()
            binding.sampleText.text = result
        }


    }

    /**
     * A native method that is implemented by the 'ledclient' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String

    companion object {
        // Used to load the 'ledclient' library on application startup.
        init {
            System.loadLibrary("ledclient")
        }
    }
}