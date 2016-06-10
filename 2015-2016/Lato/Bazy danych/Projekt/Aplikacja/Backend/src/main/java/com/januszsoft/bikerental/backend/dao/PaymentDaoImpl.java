package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Payment;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class PaymentDaoImpl implements Dao<Payment> {

  private JdbcTemplate jdbcTemplate;

  public PaymentDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Payment payment) {
    if ( payment.getId() != null && payment.getId() > 0) {
      String sql = "UPDATE payment SET rent=?, totalinpln=?, paymentdate=? WHERE id=?";

      jdbcTemplate.update(sql, payment.getRent(), payment.getTotalinpln(),
        payment.getPaymentdate(), payment.getId());
    }
    else {
      String sql = "INSERT INTO payment (rent, totalinpln, paymentdate) VALUES (?, ?, ?)";
      jdbcTemplate.update(sql, payment.getRent(), payment.getTotalinpln(), payment.getPaymentdate());
    }
  }

  @Override
  public void delete(Integer paymentID) {
    String sql = "DELETE FROM payment WHERE id=?";
    jdbcTemplate.update(sql, paymentID);
  }

  @Override
  public Payment get(Integer paymentID) {

    String sql = "SELECT * FROM payment WHERE id=" + paymentID;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Payment.class));
    if(answer.size() == 0) return null;
    else return (Payment) answer.get(0);

  }

  @Override
  public List<Payment> findall() {
    String sql = "SELECT * FROM payment";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Payment.class));
  }
}

