package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Service;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class ServiceDaoImpl implements Dao<Service> {

  private JdbcTemplate jdbcTemplate;

  public ServiceDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Service service) {
    if ( service.getId() != null && service.getId() > 0) {
      String sql = "UPDATE service SET address=?, latitude=?, longitude=? WHERE id=?";

      jdbcTemplate.update(sql, service.getAddress(), service.getLatitude(), service.getLongitude(), service.getId());
    }
    else {
      String sql = "INSERT INTO service (address) VALUES (?, ?, ?)";
      jdbcTemplate.update(sql, service.getAddress(), service.getLatitude(), service.getLongitude());
    }
  }

  @Override
  public void delete(Integer serviceID) {
    String sql = "DELETE FROM service WHERE id=?";
    jdbcTemplate.update(sql, serviceID);
  }

  @Override
  public Service get(Integer serviceID) {

    String sql = "SELECT * FROM service WHERE id=" + serviceID;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Service.class));
    if(answer.size() == 0) return null;
    else return (Service) answer.get(0);

  }

  @Override
  public List<Service> findall() {
    String sql = "SELECT * FROM service";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Service.class));
  }
}

