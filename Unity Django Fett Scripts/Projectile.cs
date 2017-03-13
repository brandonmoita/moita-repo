using UnityEngine;
using System.Collections;

public class Projectile : MonoBehaviour
{

    public float lifeTime = 2.0f;
    string _robotShooting;
    int _projectileDamage = 10;
    public GameObject Star;

    // Use this for initialization
    void Start()
    {
        Destroy(gameObject, lifeTime);
    }

    // Update is called once per frame
    void OnTriggerEnter(Collider c)
    {

        //Instantiate(Star, transform.position, transform.rotation); //comment out if you want to mark the rest of the game without crashing
        Destroy(gameObject);


    }



    public string robotShooting
    {
        get { return _robotShooting; }
        set { _robotShooting = value; }
    }

    public int projectileDamage
    {
        get { return _projectileDamage; }
        set { _projectileDamage = value; }
    }
}
