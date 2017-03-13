using UnityEngine;
using System.Collections;

public class AI : MonoBehaviour
{
    public Transform player;
    float distancefrom_player;
    public float look_range = 20.0f;
    public float agro_range = 10.0f;
    public float move_speed = 5.0f;
    public float damping = 6.0f;
    public float health = 100.0f;
    public int life = 0;
    Animator anim;
   
    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        anim = GetComponent<Animator>();
        distancefrom_player = Vector3.Distance(player.position, transform.position);
        

        if (distancefrom_player < look_range)
        {
            transform.LookAt(player);
        }

        if (distancefrom_player < agro_range)

        {
            anim.SetFloat("Speed", move_speed);
            attack();
        }
    }

    void lookAt()
    {
        Quaternion rotation = Quaternion.LookRotation(player.position - transform.position);
        transform.rotation = Quaternion.Slerp(transform.rotation, rotation, Time.deltaTime * damping);
    }

    void attack()
    {
        transform.Translate(Vector3.forward * move_speed * Time.deltaTime);
    }

    public void OnCollisionEnter(Collision boom)
    {
        //If the object that triggered this collision is tagged "Projectile"
        if (boom.gameObject.tag == "Projectile")
        {
            Debug.Log("HIT ENEMY");
            life += 10;
            if (life >= 50)
                Destroy(gameObject);
        }
    }
}